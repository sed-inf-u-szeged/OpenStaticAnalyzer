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

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.Writer;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.List;

import javax.tools.JavaFileObject;

import com.glaforge.i18n.io.CharsetToolkit;
import com.sun.source.tree.CompilationUnitTree;
import com.sun.tools.javac.api.JavacTaskImpl;
import com.sun.tools.javac.api.JavacTool;
import com.sun.tools.javac.file.JavacFileManager;
import com.sun.tools.javac.util.Context;

import columbus.logger.LoggerHandler;

class CompilerLogger extends Writer {

	private static final LoggerHandler logger = new LoggerHandler(CompilerLogger.class,
			OptionParser.getLoggerPropertyFile());

	private static final String eol = System.getProperty("line.separator");

	@Override
	public void write(char[] cbuf, int off, int len) throws IOException {
		String str = new String(cbuf, off, len);
		if (!str.equals(eol)) {
			logger.info("info.jan.CompilerLogger.compilerMessage", str);
		}
	}

	@Override
	public void flush() throws IOException {
	}

	@Override
	public void close() throws IOException {
	}
}

public class JDKTreeMaker {

	private static final LoggerHandler logger = new LoggerHandler(JDKTreeMaker.class,
			OptionParser.getLoggerPropertyFile());

	private Context context = null;

	public List<CompilationUnitTree> build(List<File> files, List<String> options) {

		List<CompilationUnitTree> tree = null;
		JavacTool compiler = JavacTool.create();

		options.add(0, "-bootclasspath");
		options.add(1, System.getProperty("sun.boot.class.path"));

		if (logger.isInfoEnabled()) {
			logger.info("info.jan.JDKTreeMaker.javacOptions");
			for (String o : options) {
				logger.info("info.jan.JDKTreeMaker.javacOption", o);
			}
		}

		Iterable<? extends JavaFileObject> fileObjects = getFileObjects(files, compiler);

		Writer writer = new CompilerLogger();

		JavacTaskImpl javacTask = (JavacTaskImpl) compiler.getTask(writer, null, null, options, null, fileObjects);

		Iterable<? extends CompilationUnitTree> trees = null;
		try {
			trees = javacTask.parse();
		} catch (Exception e) {
			logger.error("error.jan.JDKTreeMaker.javacParseError", e);
		}

		tree = new ArrayList<>();
		for (CompilationUnitTree t : trees) {
			tree.add(t);
		}

		try {
			javacTask.analyze();
		} catch (Exception e) {
			logger.error("error.jan.JDKTreeMaker.javacAnalyzeError", e);
		}

		context = javacTask.getContext();
		return tree;
	}

	private Iterable<? extends JavaFileObject> getFileObjects(List<File> files, JavacTool compiler) {
		Charset charset = null;
		Charset defaultEncoding = Charset.defaultCharset();

		Iterable<? extends JavaFileObject> fileObjects = new ArrayList<JavaFileObject>();

		if (OptionParser.encoding == null) {
			if (OptionParser.wrappedMode) {
				charset = defaultEncoding;
				logger.info("info.jan.JDKTreeMaker.defaultFileEncoding", charset.toString());
				fileObjects = getFileObjectsWithEncoding(files, compiler, charset);
			} else {
				// FIXME restore if we found a solution for PMD
				boolean detectEncoding = false;
				if (detectEncoding) {
					for (File javaFile : files) {
						try {
							byte[] buffer = new byte[4096];
							BufferedInputStream br = new BufferedInputStream(new FileInputStream(javaFile));
							br.read(buffer);

							CharsetToolkit detector = new CharsetToolkit(buffer, defaultEncoding);
							detector.setEnforce8Bit(true);
							charset = detector.guessEncoding();

							br.close();

							ArrayList<File> singleList = new ArrayList<>();
							singleList.add(javaFile);
							Iterable<? extends JavaFileObject> l = getFileObjectsWithEncoding(singleList, compiler,
									charset);
							((ArrayList<JavaFileObject>) fileObjects).addAll((ArrayList<JavaFileObject>) l);

						} catch (IOException e) {
							logger.error("error.jan.JDKTreeMaker.IOErrorWhileGuessEncoding", e);
							System.exit(1);
						}
					}
				} else {
					fileObjects = getFileObjectsWithEncoding(files, compiler, defaultEncoding);
				}
			}
		} else {
			try {
				charset = Charset.forName(OptionParser.encoding);
			} catch (Exception e) {
				logger.error("error.jan.JDKTreeMaker.cantCreateCharSet", OptionParser.encoding, e);
				System.exit(1);
			}
			fileObjects = getFileObjectsWithEncoding(files, compiler, charset);
		}

		return fileObjects;
	}

	private Iterable<? extends JavaFileObject> getFileObjectsWithEncoding(List<File> files, JavacTool compiler,
			Charset charset) {
		JavacFileManager fileManager = compiler.getStandardFileManager(null, null, charset);
		Iterable<? extends JavaFileObject> fileObjects = fileManager.getJavaFileObjectsFromFiles(files);
		return fileObjects;
	}

	public Context getContext() {
		return context;
	}
}
