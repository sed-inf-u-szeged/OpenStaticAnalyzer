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
 * Implementation class for the {@link columbus.java.asg.statm.BasicFor BasicFor} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class BasicForImpl extends BaseImpl implements BasicFor {

	private static final LoggerHandler logger = new LoggerHandler(BasicForImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected EdgeList<Comment> _comments;

	protected Object position;

	protected boolean isCompilerGenerated;

	protected boolean isToolGenerated;

	protected int _hasSubstatement;

	protected Object leftParenPosition;

	protected Object rightParenPosition;

	protected Object firstSemiPosition;

	protected Object secondSemiPosition;

	protected EdgeList<Statement> _hasInitializers;

	protected int _hasCondition;

	protected EdgeList<Statement> _hasUpdates;

	public BasicForImpl(int id, Factory factory) {
		super(id, factory);
		position = new Range(factory.getStringTable());
		leftParenPosition = new Range(factory.getStringTable());
		rightParenPosition = new Range(factory.getStringTable());
		firstSemiPosition = new Range(factory.getStringTable());
		secondSemiPosition = new Range(factory.getStringTable());
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkBasicFor;
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
	public Range getFirstSemiPosition() {
		return (Range)firstSemiPosition;
	}

	@Override
	public Range getSecondSemiPosition() {
		return (Range)secondSemiPosition;
	}

	@Override
	public void setFirstSemiPosition(Range _firstSemiPosition) {
		if (factory.getStringTable() == _firstSemiPosition.getStringTable())
			firstSemiPosition = _firstSemiPosition;
		else
			firstSemiPosition = new Range(factory.getStringTable(), _firstSemiPosition);
	}

	@Override
	public void setSecondSemiPosition(Range _secondSemiPosition) {
		if (factory.getStringTable() == _secondSemiPosition.getStringTable())
			secondSemiPosition = _secondSemiPosition;
		else
			secondSemiPosition = new Range(factory.getStringTable(), _secondSemiPosition);
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
	public EdgeIterator<Statement> getInitializersIterator() {
		if (_hasInitializers == null)
			return EdgeList.<Statement>emptyList().iterator();
		else
			return _hasInitializers.iterator();
	}

	@Override
	public boolean getInitializersIsEmpty() {
		if (_hasInitializers == null)
			return true;
		else
			return _hasInitializers.isEmpty();
	}

	@Override
	public int getInitializersSize() {
		if (_hasInitializers == null)
			return 0;
		else
			return _hasInitializers.size();
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
	public EdgeIterator<Statement> getUpdatesIterator() {
		if (_hasUpdates == null)
			return EdgeList.<Statement>emptyList().iterator();
		else
			return _hasUpdates.iterator();
	}

	@Override
	public boolean getUpdatesIsEmpty() {
		if (_hasUpdates == null)
			return true;
		else
			return _hasUpdates.isEmpty();
	}

	@Override
	public int getUpdatesSize() {
		if (_hasUpdates == null)
			return 0;
		else
			return _hasUpdates.size();
	}

	@Override
	public void addInitializers(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkStatement)) {
			if (_hasInitializers == null)
				_hasInitializers = new EdgeList<Statement>(factory);
			_hasInitializers.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addInitializers(Statement _node) {
		if (_hasInitializers == null)
			_hasInitializers = new EdgeList<Statement>(factory);
		_hasInitializers.add(_node);
		setParentEdge(_node);
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
	public void addUpdates(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkStatement)) {
			if (_hasUpdates == null)
				_hasUpdates = new EdgeList<Statement>(factory);
			_hasUpdates.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addUpdates(Statement _node) {
		if (_hasUpdates == null)
			_hasUpdates = new EdgeList<Statement>(factory);
		_hasUpdates.add(_node);
		setParentEdge(_node);
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

		io.writeInt4(((Range)firstSemiPosition).getPathKey());
		io.writeInt4(((Range)firstSemiPosition).getLine());
		io.writeInt4(((Range)firstSemiPosition).getCol());
		io.writeInt4(((Range)firstSemiPosition).getEndLine());
		io.writeInt4(((Range)firstSemiPosition).getEndCol());
		io.writeInt4(((Range)firstSemiPosition).getWideLine());
		io.writeInt4(((Range)firstSemiPosition).getWideCol());
		io.writeInt4(((Range)firstSemiPosition).getWideEndLine());
		io.writeInt4(((Range)firstSemiPosition).getWideEndCol());
		io.writeInt4(((Range)secondSemiPosition).getPathKey());
		io.writeInt4(((Range)secondSemiPosition).getLine());
		io.writeInt4(((Range)secondSemiPosition).getCol());
		io.writeInt4(((Range)secondSemiPosition).getEndLine());
		io.writeInt4(((Range)secondSemiPosition).getEndCol());
		io.writeInt4(((Range)secondSemiPosition).getWideLine());
		io.writeInt4(((Range)secondSemiPosition).getWideCol());
		io.writeInt4(((Range)secondSemiPosition).getWideEndLine());
		io.writeInt4(((Range)secondSemiPosition).getWideEndCol());


		io.writeInt4(!factory.getIsFiltered(_hasCondition) ? _hasCondition : 0);

		if (_hasInitializers != null) {
			EdgeIterator<Statement> it = getInitializersIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);

		if (_hasUpdates != null) {
			EdgeIterator<Statement> it = getUpdatesIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);
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

		((Range)firstSemiPosition).setPathKey(io.readInt4());
		((Range)firstSemiPosition).setLine(io.readInt4());
		((Range)firstSemiPosition).setCol(io.readInt4());
		((Range)firstSemiPosition).setEndLine(io.readInt4());
		((Range)firstSemiPosition).setEndCol(io.readInt4());
		((Range)firstSemiPosition).setWideLine(io.readInt4());
		((Range)firstSemiPosition).setWideCol(io.readInt4());
		((Range)firstSemiPosition).setWideEndLine(io.readInt4());
		((Range)firstSemiPosition).setWideEndCol(io.readInt4());
		((Range)secondSemiPosition).setPathKey(io.readInt4());
		((Range)secondSemiPosition).setLine(io.readInt4());
		((Range)secondSemiPosition).setCol(io.readInt4());
		((Range)secondSemiPosition).setEndLine(io.readInt4());
		((Range)secondSemiPosition).setEndCol(io.readInt4());
		((Range)secondSemiPosition).setWideLine(io.readInt4());
		((Range)secondSemiPosition).setWideCol(io.readInt4());
		((Range)secondSemiPosition).setWideEndLine(io.readInt4());
		((Range)secondSemiPosition).setWideEndCol(io.readInt4());

		_hasCondition = io.readInt4();
		if (_hasCondition != 0)
			setParentEdge(_hasCondition);


		_id = io.readInt4();
		if (_id != 0) {
			_hasInitializers = new EdgeList<Statement>(factory);
			while (_id != 0) {
				_hasInitializers.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}

		_id = io.readInt4();
		if (_id != 0) {
			_hasUpdates = new EdgeList<Statement>(factory);
			while (_id != 0) {
				_hasUpdates.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}
	}

}
