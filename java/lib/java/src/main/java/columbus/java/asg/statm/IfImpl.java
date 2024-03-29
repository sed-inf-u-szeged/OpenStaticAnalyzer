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
import columbus.java.asg.expr.Expression;
import columbus.java.asg.base.Comment;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.statm.If If} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class IfImpl extends BaseImpl implements If {

	@SuppressWarnings("unused")
	private static final LoggerHandler logger = new LoggerHandler(IfImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected EdgeList<Comment> _comments;

	protected Object position;

	protected boolean isCompilerGenerated;

	protected boolean isToolGenerated;

	protected int _hasCondition;

	protected Object elsePosition;

	protected int _hasSubstatement;

	protected int _hasFalseSubstatement;

	public IfImpl(int id, Factory factory) {
		super(id, factory);
		position = new Range(factory.getStringTable());
		elsePosition = new Range(factory.getStringTable());
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkIf;
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
	public Range getElsePosition() {
		return (Range)elsePosition;
	}

	@Override
	public void setElsePosition(Range _elsePosition) {
		if (factory.getStringTable() == _elsePosition.getStringTable())
			elsePosition = _elsePosition;
		else
			elsePosition = new Range(factory.getStringTable(), _elsePosition);
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
	public Expression getCondition() {
		if (_hasCondition == 0)
			return null;
		if (factory.getIsFiltered(_hasCondition))
			return null;
		return (Expression)factory.getRef(_hasCondition);
	}

	@Override
	public void setCondition(int _id) {
		if (_hasCondition != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasCondition" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkExpression)) {
			_hasCondition = _id;
			setParentEdge(_hasCondition);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setCondition(Expression _node) {
		if (_hasCondition != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasCondition" ));

		_hasCondition = _node.getId();
		setParentEdge(_hasCondition);
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
	public Statement getFalseSubstatement() {
		if (_hasFalseSubstatement == 0)
			return null;
		if (factory.getIsFiltered(_hasFalseSubstatement))
			return null;
		return (Statement)factory.getRef(_hasFalseSubstatement);
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
	public void setFalseSubstatement(int _id) {
		if (_hasFalseSubstatement != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasFalseSubstatement" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkStatement)) {
			_hasFalseSubstatement = _id;
			setParentEdge(_hasFalseSubstatement);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setFalseSubstatement(Statement _node) {
		if (_hasFalseSubstatement != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasFalseSubstatement" ));

		_hasFalseSubstatement = _node.getId();
		setParentEdge(_hasFalseSubstatement);
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


		io.writeInt4(!factory.getIsFiltered(_hasCondition) ? _hasCondition : 0);

		io.writeInt4(((Range)elsePosition).getPathKey());
		io.writeInt4(((Range)elsePosition).getLine());
		io.writeInt4(((Range)elsePosition).getCol());
		io.writeInt4(((Range)elsePosition).getEndLine());
		io.writeInt4(((Range)elsePosition).getEndCol());
		io.writeInt4(((Range)elsePosition).getWideLine());
		io.writeInt4(((Range)elsePosition).getWideCol());
		io.writeInt4(((Range)elsePosition).getWideEndLine());
		io.writeInt4(((Range)elsePosition).getWideEndCol());


		io.writeInt4(!factory.getIsFiltered(_hasSubstatement) ? _hasSubstatement : 0);

		io.writeInt4(!factory.getIsFiltered(_hasFalseSubstatement) ? _hasFalseSubstatement : 0);
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


		_hasCondition = io.readInt4();
		if (_hasCondition != 0)
			setParentEdge(_hasCondition);

		((Range)elsePosition).setPathKey(io.readInt4());
		((Range)elsePosition).setLine(io.readInt4());
		((Range)elsePosition).setCol(io.readInt4());
		((Range)elsePosition).setEndLine(io.readInt4());
		((Range)elsePosition).setEndCol(io.readInt4());
		((Range)elsePosition).setWideLine(io.readInt4());
		((Range)elsePosition).setWideCol(io.readInt4());
		((Range)elsePosition).setWideEndLine(io.readInt4());
		((Range)elsePosition).setWideEndCol(io.readInt4());

		_hasSubstatement = io.readInt4();
		if (_hasSubstatement != 0)
			setParentEdge(_hasSubstatement);

		_hasFalseSubstatement = io.readInt4();
		if (_hasFalseSubstatement != 0)
			setParentEdge(_hasFalseSubstatement);
	}

}
