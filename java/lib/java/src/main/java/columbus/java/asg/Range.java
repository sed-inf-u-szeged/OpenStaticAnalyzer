/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
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

package columbus.java.asg;

import columbus.StrTable;
import columbus.logger.LoggerHandler;

/**
 * Class for storing and retrieving position informations.
 */
public class Range {

	private static final LoggerHandler logger = new LoggerHandler(Range.class, Constant.LoggerPropertyFile);
	private StrTable strTable;

	private int path;

	private int line;
	private int endLine;
	private int wideLine;
	private int wideEndLine;
	private int col;

	private int endCol;

	private int wideCol;

	private int wideEndCol;

	public Range(StrTable st) {
		strTable = st;
	}

	public Range(StrTable st, String pathString, int line, int col, int endLine, int endCol, int wideLine, int wideCol, int wideEndLine, int wideEndCol) {
		strTable = st;
		setPath(pathString);
		this.line = line;
		this.col = col;
		this.endLine = endLine;
		this.endCol = endCol;
		this.wideLine = wideLine;
		this.wideCol = wideCol;
		this.wideEndLine = wideEndLine;
		this.wideEndCol = wideEndCol;
	}

	public Range(StrTable st, int pathKey, int line, int col, int endLine, int endCol, int wideLine, int wideCol, int wideEndLine, int wideEndCol) {
		strTable = st;
		path = pathKey;
		this.line = line;
		this.col = col;
		this.endLine = endLine;
		this.endCol = endCol;
		this.wideLine = wideLine;
		this.wideCol = wideCol;
		this.wideEndLine = wideEndLine;
		this.wideEndCol = wideEndCol;
	}

	public Range(StrTable st, Range range) {
		strTable = st;
		if (range.strTable == st)
			path = range.path;
		else
			path = strTable.set(range.getPath());
		line = range.line;
		endLine = range.endLine;
		wideLine = range.wideLine;
		wideEndLine = range.wideEndLine;
		col = range.col;
		endCol = range.endCol;
		wideCol = range.wideCol;
		wideEndCol = range.wideEndCol;
	}

	public Range(Range range) {
		this(range.getStringTable(), range);
	}

	public StrTable getStringTable() {
		return strTable;
	}

	public String getPath() {
		return strTable.get(path);
	}

	public int getPathKey() {
		return path;
	}

	public void setPath(String s) {
		path = strTable.set(s);
	}

	public void setPathKey(int pathKey) {
		path = pathKey;
	}

	public int getLine() {
		return line;
	}

	public void setLine(int i) {
		line = i;
	}

	public int getEndLine() {
		return endLine;
	}

	public void setEndLine(int i) {
		endLine = i;
	}

	public int getWideLine() {
		return wideLine;
	}

	public void setWideLine(int i) {
		wideLine = i;
	}

	public int getWideEndLine() {
		return wideEndLine;
	}

	public void setWideEndLine(int i) {
		wideEndLine = i;
	}

	public int getCol() {
		return col;
	}

	public void setCol(int i) {
		col = i;
	}

	public int getEndCol() {
		return endCol;
	}

	public void setEndCol(int i) {
		endCol = i;
	}

	public int getWideCol() {
		return wideCol;
	}

	public void setWideCol(int i) {
		wideCol = i;
	}

	public int getWideEndCol() {
		return wideEndCol;
	}

	public void setWideEndCol(int i) {
		wideEndCol = i;
	}

}
