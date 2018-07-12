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

package org.jan;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.TreeMap;


import columbus.java.asg.EdgeIterator;
import columbus.java.asg.Factory;
import columbus.java.asg.JavaException;
import columbus.java.asg.Range;
import columbus.java.asg.algorithms.AlgorithmPreorder;
import columbus.java.asg.base.Base;
import columbus.java.asg.base.Commentable;
import columbus.java.asg.base.Positioned;
import columbus.java.asg.struc.CompilationUnit;
import columbus.java.asg.struc.Import;
import columbus.java.asg.struc.Member;
import columbus.java.asg.struc.PackageDeclaration;
import columbus.java.asg.struc.TypeDeclaration;
import columbus.java.asg.visitors.Visitor;
import columbus.java.asg.visitors.VisitorAbstractNodes;
import columbus.logger.LoggerHandler;

import com.sun.tools.javac.parser.JANComment;
import com.sun.tools.javac.parser.Tokens.Comment.CommentStyle;

public class CommentBuilder extends Visitor {
	
	private static final LoggerHandler logger = new LoggerHandler(CommentBuilder.class, OptionParser.getLoggerPropertyFile());
	
	private Factory factory;
	private AlgorithmPreorder ap, subAP;
	private HashMap<String, ArrayList<JANComment>> comments;
	private TreeMap<Interval, ArrayList<Positioned>> map, endMap;
	
	static class Interval
	{
		private int fromLine;
		private int fromCol;
		private int toLine;
		private int toCol;
		
		public Interval(int fromLine, int fromCol, int toLine, int toCol) {
			this.fromLine = fromLine;
			this.fromCol = fromCol;
			this.toLine = toLine;
			this.toCol = toCol;
		}
		
		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + fromCol;
			result = prime * result + fromLine;
			result = prime * result + toCol;
			result = prime * result + toLine;
			return result;
		}
		
		@Override
		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (getClass() != obj.getClass())
				return false;
			Interval other = (Interval) obj;
			if (fromCol != other.fromCol)
				return false;
			if (fromLine != other.fromLine)
				return false;
			if (toCol != other.toCol)
				return false;
			if (toLine != other.toLine)
				return false;
			return true;
		}
		
		public int getFromLine() {
			return fromLine;
		}
		public void setFromLine(int fromLine) {
			this.fromLine = fromLine;
		}
		public int getFromCol() {
			return fromCol;
		}
		public void setFromCol(int fromCol) {
			this.fromCol = fromCol;
		}
		public int getToLine() {
			return toLine;
		}
		public void setToLine(int toLine) {
			this.toLine = toLine;
		}
		public int getToCol() {
			return toCol;
		}
		public void setToCol(int toCol) {
			this.toCol = toCol;
		}
		
		public String toString()
		{
			return "([" + fromLine + "," + fromCol + "]->[" + toLine + "," + toCol + "])";
		}
	}
	
	static class FromComparator implements Comparator<Interval>
	{
		@Override
		public int compare( Interval a, Interval b )
		{
			if ( a.fromLine < b.fromLine ) return -1;
			if ( a.fromLine > b.fromLine ) return 1;
			if ( a.fromCol < b.fromCol ) return -1;
			if ( a.fromCol > b.fromCol ) return 1;
			
			return 0;
		}
	}
	
	static class ToComparator implements Comparator<Interval>
	{
		@Override
		public int compare( Interval a, Interval b )
		{
			if ( a.toLine < b.toLine ) return -1;
			if ( a.toLine > b.toLine ) return 1;
			if ( a.toCol < b.toCol ) return -1;
			if ( a.toCol > b.toCol ) return 1;
			
			return 0;
		}
	}
	
	static class PositionedStartComparator implements Comparator<Positioned>
	{
		@Override
		public int compare( Positioned a, Positioned b )
		{
			Range posA = a.getPosition();
			Range posB = b.getPosition();
			if ( posA.getWideLine() < posB.getWideLine() ) return -1;
			if ( posA.getWideLine() > posB.getWideLine() ) return 1;
			if ( posA.getWideCol() < posB.getWideCol() ) return -1;
			if ( posA.getWideCol() > posB.getWideCol() ) return 1;
			return 0;
		}
	}
	
	static class PositionedEndComparator implements Comparator<Positioned>
	{
		@Override
		public int compare( Positioned a, Positioned b )
		{
			Range posA = a.getPosition();
			Range posB = b.getPosition();
			if ( posA.getWideEndLine() < posB.getWideEndLine() ) return -1;
			if ( posA.getWideEndLine() > posB.getWideEndLine() ) return 1;
			if ( posA.getWideEndCol() < posB.getWideEndCol() ) return -1;
			if ( posA.getWideEndCol() > posB.getWideEndCol() ) return 1;
			return 0;
		}
	}
	
	protected class SubTreeVisitor extends VisitorAbstractNodes
	{	
		@Override
		public void visit( Positioned p, boolean callVirtualBase )
		{
			push( p );
		}
	}
	
	public CommentBuilder( Factory factory, HashMap<String, ArrayList<JANComment>> commentMap )
	{
		this.factory = factory;
		this.comments = commentMap;
		this.ap = new AlgorithmPreorder();
		this.subAP = new AlgorithmPreorder();
		this.subAP.setVisitSpecialNodes(false, false); // traverse only the subtree and skip ap_spec nodes
		
		this.map = new TreeMap<Interval, ArrayList<Positioned>>( new FromComparator() );
		this.endMap = new TreeMap<Interval, ArrayList<Positioned>>( new ToComparator() );
	}
	
	private void push( Positioned p )
	{
		if ( p == null )
		{
			return;
		}
		
		Range position = p.getPosition();

		Interval i = new Interval
		(
			position.getWideLine()
			, position.getWideCol()
			, position.getWideEndLine()
			, position.getWideEndCol()
		);
		
		if ( ! map.containsKey(i) )
		{
			map.put( i, new ArrayList<Positioned>() );
		}
		map.get( i ).add( p );
		
		if ( ! endMap.containsKey(i) )
		{
			endMap.put( i, new ArrayList<Positioned>() );
		}
		endMap.get( i ).add( p );
	}
	
	@Override
	public void visit( CompilationUnit cu, boolean callVirtualBase  )
	{	
		// Processing the imports
		for( EdgeIterator<Import> i = cu.getImportsIterator(); i.hasNext(); )
		{
			push( i.next() );
		}

		// Processing the package declaration
		push( cu.getPackageDeclaration() );
		
		// Processing all TypeDeclarations by visiting their subtrees
		SubTreeVisitor stv = new SubTreeVisitor();
		for ( EdgeIterator<TypeDeclaration> i = cu.getTypeDeclarationsIterator(); i.hasNext(); )
		{
			TypeDeclaration next = i.next();
			subAP.run( factory, stv, next );
		}
		
		// Building the Comments in this CompilationUnit
		buildCU( cu );
		
		// Clearing the maps
		map.clear();
		endMap.clear();
	}
	
	public void build()
	{
		ap.run( factory, this );
	}
	
	private void buildCU( CompilationUnit cu )
	{
		String fileKey = cu.getPosition().getPath();
		if ( comments.containsKey( fileKey ) )
		{
			ArrayList<JANComment> fileComments = comments.get( fileKey );
			
			for ( JANComment fileComment : fileComments )
			{				
				// get a Range from the positions of the comment
				Range position = new Range( factory.getStringTable() );
				position.setPathKey( cu.getPosition().getPathKey() );
				
				int line = (int) fileComment.line();
				int col = (int) fileComment.col();
				int endLine = (int) fileComment.endLine();
				int endCol = (int) fileComment.endCol();
				
				position.setCol( col );
				position.setWideCol( col );
				position.setEndCol( endCol );
				position.setWideEndCol( endCol );
				
				position.setLine( line );
				position.setWideLine( line );
				position.setEndLine( endLine );
				position.setWideEndLine( endLine );
				
				// we search the relevant Positioned node to attach the comment to
				
				// before
				ArrayList<Positioned> pre = null;
				Entry<Interval, ArrayList<Positioned>> preEntry = map.lowerEntry( new Interval( line, col, 0, 0 ) );
				if ( preEntry != null)
				{
					pre = preEntry.getValue();
				}
				
				ArrayList<Positioned> preEnd = null;
				Entry<Interval, ArrayList<Positioned>> preEndEntry = endMap.lowerEntry( new Interval( 0, 0, endLine, endCol ) );
				if ( preEndEntry != null)
				{
					preEnd = preEndEntry.getValue();
				}
				
				// after
				ArrayList<Positioned> post = null;
				Entry<Interval, ArrayList<Positioned>> postEntry = map.higherEntry( new Interval( endLine, endCol, 0, 0 ) );
				if ( postEntry != null)
				{
					post = postEntry.getValue();
				}
				
				ArrayList<Positioned> postEnd = null;
				Entry<Interval, ArrayList<Positioned>> postEndEntry = endMap.higherEntry( new Interval( 0, 0, endLine, endCol ) );
				if ( postEndEntry != null)
				{
					postEnd = postEndEntry.getValue();
				}
				
				// the node that starts right before this is not in the same scope
				// if it also starts after something that ends right before the current node
				boolean preIsInOtherScope = false;
				if ( pre != null && preEnd != null )
				{
					Interval firstStart = preEntry.getKey();
					// transfer Tos to Froms for comparison
					Interval firstEnd = new Interval(
						preEndEntry.getKey().getToLine()
						, preEndEntry.getKey().getToCol()
						, 0, 0
					);
					if ( new FromComparator().compare(firstEnd, firstStart) < 0 )
					{
						preIsInOtherScope = true;
					}
				}
				
				// the node that starts right after this is not in the same scope
				// if it also starts after something that encloses the current node
				boolean postIsInOtherScope = false;
				if ( post != null && postEnd != null )
				{
					Interval firstStart = postEntry.getKey();
					// transfer Tos to Froms for comparison
					Interval firstEnd = new Interval(
						postEndEntry.getKey().getToLine()
						, postEndEntry.getKey().getToCol()
						, 0, 0
					);
					if ( new FromComparator().compare(firstEnd, firstStart) < 0 )
					{
						postIsInOtherScope = true;
					}
				}
				
				/*
				 * Javadocs are supposed to immediately precede a Member
				 * if that's the case, it gets attached
				 * if not, it's treated as a simple block comment
				 */
				if ( fileComment.style() == CommentStyle.JAVADOC )
				{
					if ( post != null )
					{
						Commentable toNode = null;
						boolean packageInfo = cu.getPosition().getPath().endsWith("package-info.java");
						
						for ( Positioned p : post )
						{
							if ( packageInfo && p instanceof PackageDeclaration )
							{
								// Separate treatment for package-level comments
								toNode = ((PackageDeclaration)p).getRefersTo();
								break;
							}
							else if ( p instanceof Member )
							{
								toNode = p;
								break;
							}
						}
						
						if ( toNode != null )
						{
							attach( toNode, fileComment, position );
							continue;
						}
					}
					fileComment.style( CommentStyle.BLOCK );
				}
				
				/*
				 * A line comment (in our estimation) belongs to:
				 * - (1) either the "highest rank" preceding node, while it's on the same line
				 * - (2) or the highest rank node immediately following the comment ( if it's in the same scope )
				 * - (3) if there's nothing on the same line or after, then the node before (wherever it is)
				 * - (4) if there's nothing before of after, the comment gets attached to the CU  itself
				 */
				if ( fileComment.style() == CommentStyle.LINE )
				{
					Commentable node = null;
					Positioned temp = null;
					if ( pre != null )
					{
						Collections.sort( pre, new PositionedEndComparator() );
						temp = pre.get( pre.size() - 1 );
						if ( temp.getPosition().getWideLine() == line )
						{
							node = highestInLine( temp, line ); // (1)
						}
						else if ( (post == null || postIsInOtherScope) )
						{
							if ( preIsInOtherScope )
							{
								node = highestInLine( temp, temp.getPosition().getWideLine() ); // (3)
							}
							else if ( preEnd != null )
							{
								Collections.sort( preEnd, new PositionedStartComparator() );
								node = preEnd.get( 0 ); // (3)
							}
						}
					}
					if ( node == null && post != null )
					{
						Collections.sort( post, new PositionedEndComparator() );
						node = post.get( post.size() - 1 ); // (2)
					}
					if ( node == null )
					{
						node = cu; // (4)
					}
	
					attach( node, fileComment, position );
					continue;
				}
				
				/*
				 * The same applies to a block comment (or a degraded javadoc), only if the
				 * node is in the same line (preceding the comment), the "highest rank" search
				 * is modified so that the comment gets attached to the highest rank node that 
				 * ENDS immediately before it. 
				 * For example:
				 * 
				 * for ( int i = 1; / * starts at 1 because 0 is invalid * / i < max; ++i ) { ... }
				 * 
				 * In this case the comment belongs to the assignment, not the for statement.
				 */
				if ( fileComment.style() == CommentStyle.BLOCK )
				{
					Commentable node = null;
					if ( preEnd != null && ! preIsInOtherScope )
					{
						Collections.sort( preEnd, new PositionedStartComparator() );
						Positioned temp = preEnd.get( 0 );
						if ( temp.getPosition().getWideLine() == line || post == null || postIsInOtherScope )
						{
							node = temp; // (1,3)
						}
					}
					if ( node == null && pre != null && ( post == null || postIsInOtherScope ) )
					{
						Collections.sort( pre, new PositionedEndComparator() );
						node = pre.get( pre.size() - 1 ); // (3)
					}
					if ( node == null && post != null )
					{
						Collections.sort( post, new PositionedEndComparator() );
						node = post.get( post.size() - 1 ); // (2)
					}
					if ( node == null )
					{
						node = cu; // (4)
					}
					attach( node, fileComment, position );
				}
			}
		}
		
		comments.remove( fileKey );
	}

	private void attach( Commentable target, JANComment c, Range r )
	{
		columbus.java.asg.base.Comment node;
		String text = c.text();
		// we build the corresponding Comment node
		switch( c.style() )
		{
		case LINE:
			node = factory.createLineComment(r, text);
			break;
		case BLOCK:
			node = factory.createBlockComment(r, text);
			break;
		case JAVADOC:
			node = factory.createJavadocComment(r, text);
			break;
		default:
			throw new JavaException(logger.formatMessage("ex.jan.CommentBuilder.unknownCommentStyle", c.style()));
		}
		// and attach it to the Positioned node where it (most likely) belongs
		target.addComments( node );
	}
	
	private Positioned highestInLine( Positioned p, int line )
	{
		Positioned result = null;
		do
		{
			result = p;
			Base parent = p.getParent();
			
			if ( parent == null ) break;
			if ( ! ( parent instanceof Positioned ) ) break;
			
			p = (Positioned) parent;
		}
		while ( p.getPosition().getWideLine() == line );
		return result;
	}
}
