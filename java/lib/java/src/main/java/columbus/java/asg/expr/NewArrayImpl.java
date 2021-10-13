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

package columbus.java.asg.expr;

import columbus.IO;
import columbus.java.asg.*;
import columbus.java.asg.base.BaseImpl;
import columbus.java.asg.base.Base;
import columbus.java.asg.type.Type;
import columbus.java.asg.base.Comment;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.expr.NewArray NewArray} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class NewArrayImpl extends BaseImpl implements NewArray {

	@SuppressWarnings("unused")
	private static final LoggerHandler logger = new LoggerHandler(NewArrayImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected EdgeList<Comment> _comments;

	protected Object position;

	protected boolean isCompilerGenerated;

	protected boolean isToolGenerated;

	protected int _type;

	protected Object leftBracePosition;

	protected int _hasComponentType;

	protected EdgeList<Expression> _hasDimensions;

	protected EdgeList<Expression> _hasInitializers;

	public NewArrayImpl(int id, Factory factory) {
		super(id, factory);
		position = new Range(factory.getStringTable());
		leftBracePosition = new Range(factory.getStringTable());
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkNewArray;
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
	public Range getLeftBracePosition() {
		return (Range)leftBracePosition;
	}

	@Override
	public void setLeftBracePosition(Range _leftBracePosition) {
		if (factory.getStringTable() == _leftBracePosition.getStringTable())
			leftBracePosition = _leftBracePosition;
		else
			leftBracePosition = new Range(factory.getStringTable(), _leftBracePosition);
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
	public Type getType() {
		if (_type == 0)
			return null;
		if (factory.getIsFiltered(_type))
			return null;
		return (Type)factory.getRef(_type);
	}

	@Override
	public void setType(int _id) {
		if (_type != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","type" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkType)) {
			_type = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setType(Type _node) {
		if (_type != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","type" ));

		_type = _node.getId();
	}

	@Override
	public TypeExpression getComponentType() {
		if (_hasComponentType == 0)
			return null;
		if (factory.getIsFiltered(_hasComponentType))
			return null;
		return (TypeExpression)factory.getRef(_hasComponentType);
	}

	@Override
	public EdgeIterator<Expression> getDimensionsIterator() {
		if (_hasDimensions == null)
			return EdgeList.<Expression>emptyList().iterator();
		else
			return _hasDimensions.iterator();
	}

	@Override
	public boolean getDimensionsIsEmpty() {
		if (_hasDimensions == null)
			return true;
		else
			return _hasDimensions.isEmpty();
	}

	@Override
	public int getDimensionsSize() {
		if (_hasDimensions == null)
			return 0;
		else
			return _hasDimensions.size();
	}

	@Override
	public EdgeIterator<Expression> getInitializersIterator() {
		if (_hasInitializers == null)
			return EdgeList.<Expression>emptyList().iterator();
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
	public void setComponentType(int _id) {
		if (_hasComponentType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasComponentType" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkTypeExpression)) {
			_hasComponentType = _id;
			setParentEdge(_hasComponentType);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setComponentType(TypeExpression _node) {
		if (_hasComponentType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasComponentType" ));

		_hasComponentType = _node.getId();
		setParentEdge(_hasComponentType);
	}

	@Override
	public void addDimensions(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkExpression)) {
			if (_hasDimensions == null)
				_hasDimensions = new EdgeList<Expression>(factory);
			_hasDimensions.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addDimensions(Expression _node) {
		if (_hasDimensions == null)
			_hasDimensions = new EdgeList<Expression>(factory);
		_hasDimensions.add(_node);
		setParentEdge(_node);
	}

	@Override
	public void addInitializers(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkExpression)) {
			if (_hasInitializers == null)
				_hasInitializers = new EdgeList<Expression>(factory);
			_hasInitializers.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addInitializers(Expression _node) {
		if (_hasInitializers == null)
			_hasInitializers = new EdgeList<Expression>(factory);
		_hasInitializers.add(_node);
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


		io.writeInt4(!factory.getIsFiltered(_type) ? _type : 0);

		io.writeInt4(((Range)leftBracePosition).getPathKey());
		io.writeInt4(((Range)leftBracePosition).getLine());
		io.writeInt4(((Range)leftBracePosition).getCol());
		io.writeInt4(((Range)leftBracePosition).getEndLine());
		io.writeInt4(((Range)leftBracePosition).getEndCol());
		io.writeInt4(((Range)leftBracePosition).getWideLine());
		io.writeInt4(((Range)leftBracePosition).getWideCol());
		io.writeInt4(((Range)leftBracePosition).getWideEndLine());
		io.writeInt4(((Range)leftBracePosition).getWideEndCol());


		io.writeInt4(!factory.getIsFiltered(_hasComponentType) ? _hasComponentType : 0);

		if (_hasDimensions != null) {
			EdgeIterator<Expression> it = getDimensionsIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);

		if (_hasInitializers != null) {
			EdgeIterator<Expression> it = getInitializersIterator();
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


		_type = io.readInt4();

		((Range)leftBracePosition).setPathKey(io.readInt4());
		((Range)leftBracePosition).setLine(io.readInt4());
		((Range)leftBracePosition).setCol(io.readInt4());
		((Range)leftBracePosition).setEndLine(io.readInt4());
		((Range)leftBracePosition).setEndCol(io.readInt4());
		((Range)leftBracePosition).setWideLine(io.readInt4());
		((Range)leftBracePosition).setWideCol(io.readInt4());
		((Range)leftBracePosition).setWideEndLine(io.readInt4());
		((Range)leftBracePosition).setWideEndCol(io.readInt4());

		_hasComponentType = io.readInt4();
		if (_hasComponentType != 0)
			setParentEdge(_hasComponentType);


		_id = io.readInt4();
		if (_id != 0) {
			_hasDimensions = new EdgeList<Expression>(factory);
			while (_id != 0) {
				_hasDimensions.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}

		_id = io.readInt4();
		if (_id != 0) {
			_hasInitializers = new EdgeList<Expression>(factory);
			while (_id != 0) {
				_hasInitializers.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}
	}

}
