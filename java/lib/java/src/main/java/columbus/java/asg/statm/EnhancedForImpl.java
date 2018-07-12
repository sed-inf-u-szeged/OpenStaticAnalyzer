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

package columbus.java.asg.statm;

import columbus.IO;
import columbus.java.asg.*;
import columbus.java.asg.base.BaseImpl;
import columbus.java.asg.base.Base;
import columbus.java.asg.struc.Parameter;
import columbus.java.asg.expr.Expression;
import columbus.java.asg.base.Comment;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.statm.EnhancedFor EnhancedFor} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class EnhancedForImpl extends BaseImpl implements EnhancedFor {

	private static final LoggerHandler logger = new LoggerHandler(EnhancedForImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected EdgeList<Comment> _comments;

	protected Object position;

	protected boolean isCompilerGenerated;

	protected boolean isToolGenerated;

	protected int _hasSubstatement;

	protected Object leftParenPosition;

	protected Object rightParenPosition;

	protected Object colonPosition;

	protected int _hasParameter;

	protected int _hasExpression;

	public EnhancedForImpl(int id, Factory factory) {
		super(id, factory);
		position = new Range(factory.getStringTable());
		leftParenPosition = new Range(factory.getStringTable());
		rightParenPosition = new Range(factory.getStringTable());
		colonPosition = new Range(factory.getStringTable());
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkEnhancedFor;
	}

	@Override
	public Range getPosition() {
		return (Range)position;
	}

	@Override
	public void setPosition(Range _position) {
		if (factory.getStringTable() == _position.getStringTable())
			position = _position;
		else
			position = new Range(factory.getStringTable(), _position);
	}

	@Override
	public boolean getIsCompilerGenerated() {
		return isCompilerGenerated;
	}

	@Override
	public boolean getIsToolGenerated() {
		return isToolGenerated;
	}

	@Override
	public void setIsCompilerGenerated(boolean _isCompilerGenerated) {
		isCompilerGenerated = _isCompilerGenerated;
	}

	@Override
	public void setIsToolGenerated(boolean _isToolGenerated) {
		isToolGenerated = _isToolGenerated;
	}

	@Override
	public Range getLeftParenPosition() {
		return (Range)leftParenPosition;
	}

	@Override
	public Range getRightParenPosition() {
		return (Range)rightParenPosition;
	}

	@Override
	public void setLeftParenPosition(Range _leftParenPosition) {
		if (factory.getStringTable() == _leftParenPosition.getStringTable())
			leftParenPosition = _leftParenPosition;
		else
			leftParenPosition = new Range(factory.getStringTable(), _leftParenPosition);
	}

	@Override
	public void setRightParenPosition(Range _rightParenPosition) {
		if (factory.getStringTable() == _rightParenPosition.getStringTable())
			rightParenPosition = _rightParenPosition;
		else
			rightParenPosition = new Range(factory.getStringTable(), _rightParenPosition);
	}

	@Override
	public Range getColonPosition() {
		return (Range)colonPosition;
	}

	@Override
	public void setColonPosition(Range _colonPosition) {
		if (factory.getStringTable() == _colonPosition.getStringTable())
			colonPosition = _colonPosition;
		else
			colonPosition = new Range(factory.getStringTable(), _colonPosition);
	}

	@Override
	public EdgeIterator<Comment> getCommentsIterator() {
		if (_comments == null)
			return EdgeList.<Comment>emptyList().iterator();
		else
			return _comments.iterator();
	}

	@Override
	public boolean getCommentsIsEmpty() {
		if (_comments == null)
			return true;
		else
			return _comments.isEmpty();
	}

	@Override
	public int getCommentsSize() {
		if (_comments == null)
			return 0;
		else
			return _comments.size();
	}

	@Override
	public void addComments(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkComment)) {
			if (_comments == null)
				_comments = new EdgeList<Comment>(factory);
			_comments.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void addComments(Comment _node) {
		if (_comments == null)
			_comments = new EdgeList<Comment>(factory);
		_comments.add(_node);
	}

	@Override
	public Statement getSubstatement() {
		if (_hasSubstatement == 0)
			return null;
		if (factory.getIsFiltered(_hasSubstatement))
			return null;
		return (Statement)factory.getRef(_hasSubstatement);
	}

	@Override
	public void setSubstatement(int _id) {
		if (_hasSubstatement != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasSubstatement" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkStatement)) {
			_hasSubstatement = _id;
			setParentEdge(_hasSubstatement);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setSubstatement(Statement _node) {
		if (_hasSubstatement != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasSubstatement" ));

		_hasSubstatement = _node.getId();
		setParentEdge(_hasSubstatement);
	}

	@Override
	public Parameter getParameter() {
		if (_hasParameter == 0)
			return null;
		if (factory.getIsFiltered(_hasParameter))
			return null;
		return (Parameter)factory.getRef(_hasParameter);
	}

	@Override
	public Expression getExpression() {
		if (_hasExpression == 0)
			return null;
		if (factory.getIsFiltered(_hasExpression))
			return null;
		return (Expression)factory.getRef(_hasExpression);
	}

	@Override
	public void setParameter(int _id) {
		if (_hasParameter != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasParameter" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkParameter) {
			_hasParameter = _id;
			setParentEdge(_hasParameter);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setParameter(Parameter _node) {
		if (_hasParameter != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasParameter" ));

		_hasParameter = _node.getId();
		setParentEdge(_hasParameter);
	}

	@Override
	public void setExpression(int _id) {
		if (_hasExpression != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasExpression" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkExpression)) {
			_hasExpression = _id;
			setParentEdge(_hasExpression);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setExpression(Expression _node) {
		if (_hasExpression != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasExpression" ));

		_hasExpression = _node.getId();
		setParentEdge(_hasExpression);
	}


	// ---------- Accept methods for Visitor ----------

	@Override
	public void accept(Visitor visitor) {
		visitor.visit(this, true);
	}

	@Override
	public void acceptEnd(Visitor visitor) {
		visitor.visitEnd(this, true);
	}


	// ---------- Save ----------

	@Override
	public void save(IO io) {
		io.writeInt4(id);
		io.writeUShort2(getNodeKind().ordinal());


		if (_comments != null) {
			EdgeIterator<Comment> it = getCommentsIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);

		io.writeInt4(((Range)position).getPathKey());
		io.writeInt4(((Range)position).getLine());
		io.writeInt4(((Range)position).getCol());
		io.writeInt4(((Range)position).getEndLine());
		io.writeInt4(((Range)position).getEndCol());
		io.writeInt4(((Range)position).getWideLine());
		io.writeInt4(((Range)position).getWideCol());
		io.writeInt4(((Range)position).getWideEndLine());
		io.writeInt4(((Range)position).getWideEndCol());
		{
			byte boolValues = 0;
			boolValues <<= 1;
			if (isCompilerGenerated) 
				boolValues |= 1;
			boolValues <<= 1;
			if (isToolGenerated) 
				boolValues |= 1;
			io.writeByte1(boolValues);
		}


		io.writeInt4(!factory.getIsFiltered(_hasSubstatement) ? _hasSubstatement : 0);

		io.writeInt4(((Range)leftParenPosition).getPathKey());
		io.writeInt4(((Range)leftParenPosition).getLine());
		io.writeInt4(((Range)leftParenPosition).getCol());
		io.writeInt4(((Range)leftParenPosition).getEndLine());
		io.writeInt4(((Range)leftParenPosition).getEndCol());
		io.writeInt4(((Range)leftParenPosition).getWideLine());
		io.writeInt4(((Range)leftParenPosition).getWideCol());
		io.writeInt4(((Range)leftParenPosition).getWideEndLine());
		io.writeInt4(((Range)leftParenPosition).getWideEndCol());
		io.writeInt4(((Range)rightParenPosition).getPathKey());
		io.writeInt4(((Range)rightParenPosition).getLine());
		io.writeInt4(((Range)rightParenPosition).getCol());
		io.writeInt4(((Range)rightParenPosition).getEndLine());
		io.writeInt4(((Range)rightParenPosition).getEndCol());
		io.writeInt4(((Range)rightParenPosition).getWideLine());
		io.writeInt4(((Range)rightParenPosition).getWideCol());
		io.writeInt4(((Range)rightParenPosition).getWideEndLine());
		io.writeInt4(((Range)rightParenPosition).getWideEndCol());

		io.writeInt4(((Range)colonPosition).getPathKey());
		io.writeInt4(((Range)colonPosition).getLine());
		io.writeInt4(((Range)colonPosition).getCol());
		io.writeInt4(((Range)colonPosition).getEndLine());
		io.writeInt4(((Range)colonPosition).getEndCol());
		io.writeInt4(((Range)colonPosition).getWideLine());
		io.writeInt4(((Range)colonPosition).getWideCol());
		io.writeInt4(((Range)colonPosition).getWideEndLine());
		io.writeInt4(((Range)colonPosition).getWideEndCol());


		io.writeInt4(!factory.getIsFiltered(_hasParameter) ? _hasParameter : 0);

		io.writeInt4(!factory.getIsFiltered(_hasExpression) ? _hasExpression : 0);
	}


	// ---------- Load ----------

	@Override
	public void load(IO io) {
		int _id;



		_id = io.readInt4();
		if (_id != 0) {
			_comments = new EdgeList<Comment>(factory);
			while (_id != 0) {
				_comments.add(_id);
				_id = io.readInt4();
			}
		}

		((Range)position).setPathKey(io.readInt4());
		((Range)position).setLine(io.readInt4());
		((Range)position).setCol(io.readInt4());
		((Range)position).setEndLine(io.readInt4());
		((Range)position).setEndCol(io.readInt4());
		((Range)position).setWideLine(io.readInt4());
		((Range)position).setWideCol(io.readInt4());
		((Range)position).setWideEndLine(io.readInt4());
		((Range)position).setWideEndCol(io.readInt4());
		{
			byte boolValues = io.readByte1();
			isToolGenerated = (boolValues & 1) != 0;
			boolValues >>>= 1;
			isCompilerGenerated = (boolValues & 1) != 0;
			boolValues >>>= 1;
		}


		_hasSubstatement = io.readInt4();
		if (_hasSubstatement != 0)
			setParentEdge(_hasSubstatement);

		((Range)leftParenPosition).setPathKey(io.readInt4());
		((Range)leftParenPosition).setLine(io.readInt4());
		((Range)leftParenPosition).setCol(io.readInt4());
		((Range)leftParenPosition).setEndLine(io.readInt4());
		((Range)leftParenPosition).setEndCol(io.readInt4());
		((Range)leftParenPosition).setWideLine(io.readInt4());
		((Range)leftParenPosition).setWideCol(io.readInt4());
		((Range)leftParenPosition).setWideEndLine(io.readInt4());
		((Range)leftParenPosition).setWideEndCol(io.readInt4());
		((Range)rightParenPosition).setPathKey(io.readInt4());
		((Range)rightParenPosition).setLine(io.readInt4());
		((Range)rightParenPosition).setCol(io.readInt4());
		((Range)rightParenPosition).setEndLine(io.readInt4());
		((Range)rightParenPosition).setEndCol(io.readInt4());
		((Range)rightParenPosition).setWideLine(io.readInt4());
		((Range)rightParenPosition).setWideCol(io.readInt4());
		((Range)rightParenPosition).setWideEndLine(io.readInt4());
		((Range)rightParenPosition).setWideEndCol(io.readInt4());

		((Range)colonPosition).setPathKey(io.readInt4());
		((Range)colonPosition).setLine(io.readInt4());
		((Range)colonPosition).setCol(io.readInt4());
		((Range)colonPosition).setEndLine(io.readInt4());
		((Range)colonPosition).setEndCol(io.readInt4());
		((Range)colonPosition).setWideLine(io.readInt4());
		((Range)colonPosition).setWideCol(io.readInt4());
		((Range)colonPosition).setWideEndLine(io.readInt4());
		((Range)colonPosition).setWideEndCol(io.readInt4());

		_hasParameter = io.readInt4();
		if (_hasParameter != 0)
			setParentEdge(_hasParameter);

		_hasExpression = io.readInt4();
		if (_hasExpression != 0)
			setParentEdge(_hasExpression);
	}

}
