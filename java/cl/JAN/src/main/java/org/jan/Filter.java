/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

package org.jan;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import columbus.java.asg.Factory;
import columbus.java.asg.algorithms.AlgorithmPreorder;
import columbus.java.asg.base.Base;
import columbus.java.asg.visitors.VisitorAbstractNodes;
import columbus.logger.LoggerHandler;

public class Filter {

	private static final LoggerHandler logger = new LoggerHandler(Filter.class, OptionParser.getLoggerPropertyFile());

	private Factory factory;
	private int nodesAfterExternalClasses;
	private boolean[] visitedNodes;

	public Filter(Factory factory, int nodesBeforeExternalClasses, int nodesAfterExternalClasses) {
		this.factory = factory;
		this.nodesAfterExternalClasses = nodesAfterExternalClasses;
		this.visitedNodes = new boolean[factory.size()];

		for (int i = nodesBeforeExternalClasses; i < nodesAfterExternalClasses; ++i) {
			// the nodes that were built from external classes are automatically filtered out
			factory.setFilteredThisNodeOnly(i);
		}
	}

	protected class UsedNodesVisitor extends VisitorAbstractNodes {
		@Override
		public void visit(Base node, boolean callVirtualBase) {
			visitedNodes[node.getId()] = true;
		}
	}

	public void run() {
		AlgorithmPreorder ap = new AlgorithmPreorder();
		ap.setVisitSpecialNodes(true, true);
		UsedNodesVisitor visitor = new UsedNodesVisitor();
		// traverse the internal nodes and the referred types
		ap.run(factory, visitor, factory.getRoot());

		// filter out types that are used only by filtered nodes
		for (int i = nodesAfterExternalClasses; i < factory.size(); ++i) {
			if (!visitedNodes[i]) {
				factory.setFilteredThisNodeOnly(i);
			}
		}
	}

	public static boolean filterList(List<File> inputs, final String hardFilterFilePath) {
		List<String> lines = new LinkedList<String>();
		// open the filter pattern file
		try (BufferedReader reader = new BufferedReader(new FileReader(new File(hardFilterFilePath)))) {
			String line;
			while ((line = reader.readLine()) != null) {
				if (line.startsWith("-") || line.startsWith("+")) {
					lines.add(0, line);
				}
			}
		} catch (IOException e) {
			logger.error("error.jan.Filter.badHardFilter", e);
			return false;
		}
		Iterator<File> it = inputs.iterator();
		while (it.hasNext()) {
			File inputFileName = it.next();
			for (String filterLine : lines) {
				String regexp = ".*" + filterLine.substring(1) + ".*";
				Pattern pattern = null;
				if (System.getProperty("os.name").contains("Windows")){
					pattern = Pattern.compile(regexp, Pattern.CASE_INSENSITIVE);
				} else {
					pattern = Pattern.compile(regexp);
				}
				
				Matcher m = pattern.matcher(inputFileName.getAbsolutePath());
				if (m.matches()) {
					if (filterLine.startsWith("-")) {
						if (logger.isDebugEnabled()) {
							logger.debug("debug.jan.Filter.skippingFileByHardFilter", inputFileName.getAbsolutePath());
						}
						it.remove();
					}
					break;
				}
			}
		}
		return true;
	}

}
