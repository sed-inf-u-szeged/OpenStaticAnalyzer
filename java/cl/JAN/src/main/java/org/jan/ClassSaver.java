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

import java.io.File;

import columbus.CsiHeader;
import columbus.StrTable.StrType;
import columbus.java.asg.Common;
import columbus.java.asg.Factory;
import columbus.java.asg.Factory.Iterator;
import columbus.java.asg.algorithms.AlgorithmPreorder;
import columbus.java.asg.base.Base;
import columbus.java.asg.enums.NodeKind;
import columbus.java.asg.struc.Package;
import columbus.java.asg.struc.TypeDeclaration;
import columbus.java.asg.visitors.VisitorJAVAML;
import columbus.java.asg.visitors.VisitorSpecFilter;
import columbus.logger.LoggerHandler;

public class ClassSaver {

	private static final LoggerHandler logger = new LoggerHandler(ClassSaver.class,
			OptionParser.getLoggerPropertyFile());

	public static void saveClasses(Factory fact, String outDir, String extraAsg, CsiHeader header) {
		AlgorithmPreorder preorder = new AlgorithmPreorder();
		preorder.setVisitSpecialNodes(false, false);
		VisitorSpecFilter visitor = new VisitorSpecFilter(fact);

		// determining the path of the extra jsi
		if (extraAsg == null) {
			logger.error("error.jan.ClassSaver.missingDirectoryOfExtraAsg");
		} else {
			int no = 0;
			while (new File(extraAsg, "extra" + (++no) + ".jsi").exists())
				;
			extraAsg += File.separator + "extra" + no;
		}

		fact.turnFilterOff();

		Iterator it = fact.iterator();
		while (it.hasNext()) {
			fact.turnFilterOff();
			Base node = it.next();
			if (node.getParent() == null || !Common.getIsTypeDeclaration(node)
					|| node.getParent().getNodeKind() != NodeKind.ndkPackage
					|| ((TypeDeclaration) node).getIsInCompilationUnit() == null) {
				continue;
			}

			visitor.init();

			visitor.addRoot(node);
			visitor.addRef(((TypeDeclaration) node).getIsInCompilationUnit());
			visitor.run();

			visitor.createFilter();
			fact.turnFilterOn();

			String path = "";
			if (outDir == null) {
				String tmpPath = ((TypeDeclaration) node).getPosition().getPath();
				String parent = new File(tmpPath).getParent();
				path = (parent != null ? parent : ".") + File.separator;
			} else {
				path = outDir + File.separator;
				if (node.getParent() != fact.getRoot()
						&& !((Package) node.getParent()).getName().equals("unnamed package")) {
					path += ((Package) node.getParent()).getQualifiedName().replace('.', File.separatorChar);
					path += File.separator;
				}
			}

			if (OptionParser.getColumbusResultDir() != null) {
				path += OptionParser.getColumbusResultDir() + File.separator;
			}
			path += ((TypeDeclaration) node).getName();

			if (extraAsg != null)
				header.add("ExtraAsg", extraAsg + ".jsi");

			saveToSmallJsi(fact, path + ".jsi", header);
			if (OptionParser.isXmlToEveryClass()) {
				saveToXml(fact, path + ".jml");
			}

			visitor.restoreStrTable();
		}

		// saving extra jsi
		if (extraAsg != null) {
			fact.turnFilterOff();
			visitor.init();

			it = fact.iterator();
			while (it.hasNext()) {
				Base node = it.next();
				if (node.getParent() == null || !Common.getIsTypeDeclaration(node)
						|| node.getParent().getNodeKind() != NodeKind.ndkPackage
						|| ((TypeDeclaration) node).getIsInCompilationUnit() != null) {
					continue;
				}
				visitor.addRoot(node);
			}

			visitor.run();
			visitor.createFilter();

			fact.turnFilterOn();

			saveToSmallJsi(fact, extraAsg + ".jsi", new CsiHeader());
			if (OptionParser.isXmlToEveryClass()) {
				saveToXml(fact, extraAsg + ".xml");
			}

			visitor.restoreStrTable();
		}
	}

	private static void createParentDirectory(String filename) {
		File dir = new File(filename).getParentFile();
		if (dir != null && !dir.exists())
			dir.mkdirs();
	}

	public static void saveToXml(Factory fact, String xmlPath) {
		createParentDirectory(xmlPath);
		VisitorJAVAML vis = new VisitorJAVAML(xmlPath, "", false);
		AlgorithmPreorder algPre = new AlgorithmPreorder();
		algPre.run(fact, vis);
	}

	public static void saveToJsi(Factory fact, String jsiPath, CsiHeader header) {
		String timestamp = Long.toString(System.currentTimeMillis());
		header.add("TimeStamp", timestamp);
		logger.info("info.jan.classSaver.savingFileTimestamp", timestamp);
		if (OptionParser.getComponentId() != null) {
			header.add(CsiHeader.csih_OriginalLocation, OptionParser.getComponentId());
		}
		if (OptionParser.getChangesetID() != null) {
			header.add(CsiHeader.csih_ChangesetID, OptionParser.getChangesetID());
		}
		saveToJsi(fact, jsiPath, header, true, false, StrType.strDefault);
	}

	private static void saveToSmallJsi(Factory fact, String jsiPath, CsiHeader header) {
		saveToJsi(fact, jsiPath, header, false, true, StrType.strToSave);
	}

	private static void saveToJsi(Factory fact, String jsiPath, CsiHeader header, boolean saveFilter,
			boolean usedSpecNodesOnly, StrType strType) {
		createParentDirectory(jsiPath);
		// save jsi
		logger.debug("debug.jan.classSaver.savingFile", jsiPath);
		fact.save(jsiPath, header, strType, usedSpecNodesOnly);

		if (saveFilter) {
			// save filter
			String filterPath = jsiPath;
			int idx = filterPath.lastIndexOf('.');
			if (idx != -1) {
				filterPath = filterPath.substring(0, idx) + ".fjsi";
			} else {
				filterPath += ".fjsi";
			}
			fact.saveFilter(filterPath);
		}
	}
}
