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
import columbus.java.asg.struc.AnonymousClass;
import columbus.java.asg.struc.NormalMethod;
import columbus.java.asg.type.Type;
import columbus.java.asg.base.Comment;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.expr.NewClass NewClass} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class NewClassImpl extends BaseImpl implements NewClass {

	private static final LoggerHandler logger = new LoggerHandler(NewClassImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected EdgeList<Comment> _comments;

	protected Object position;

	protected boolean isCompilerGenerated;

	protected boolean isToolGenerated;

	protected int _type;

	protected int _hasEnclosingExpression;

	protected EdgeList<TypeExpression> _hasTypeArguments;

	protected int _hasTypeName;

	protected EdgeList<Expression> _hasArguments;

	protected int _hasAnonymousClass;

	protected int _constructor;

	public NewClassImpl(int id, Factory factory) {
		super(id, factory);
		position = new Range(factory.getStringTable());
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkNewClass;
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
	public Expression getEnclosingExpression() {
		if (_hasEnclosingExpression == 0)
			return null;
		if (factory.getIsFiltered(_hasEnclosingExpression))
			return null;
		return (Expression)factory.getRef(_hasEnclosingExpression);
	}

	@Override
	public EdgeIterator<TypeExpression> getTypeArgumentsIterator() {
		if (_hasTypeArguments == null)
			return EdgeList.<TypeExpression>emptyList().iterator();
		else
			return _hasTypeArguments.iterator();
	}

	@Override
	public boolean getTypeArgumentsIsEmpty() {
		if (_hasTypeArguments == null)
			return true;
		else
			return _hasTypeArguments.isEmpty();
	}

	@Override
	public int getTypeArgumentsSize() {
		if (_hasTypeArguments == null)
			return 0;
		else
			return _hasTypeArguments.size();
	}

	@Override
	public TypeExpression getTypeName() {
		if (_hasTypeName == 0)
			return null;
		if (factory.getIsFiltered(_hasTypeName))
			return null;
		return (TypeExpression)factory.getRef(_hasTypeName);
	}

	@Override
	public EdgeIterator<Expression> getArgumentsIterator() {
		if (_hasArguments == null)
			return EdgeList.<Expression>emptyList().iterator();
		else
			return _hasArguments.iterator();
	}

	@Override
	public boolean getArgumentsIsEmpty() {
		if (_hasArguments == null)
			return true;
		else
			return _hasArguments.isEmpty();
	}

	@Override
	public int getArgumentsSize() {
		if (_hasArguments == null)
			return 0;
		else
			return _hasArguments.size();
	}

	@Override
	public AnonymousClass getAnonymousClass() {
		if (_hasAnonymousClass == 0)
			return null;
		if (factory.getIsFiltered(_hasAnonymousClass))
			return null;
		return (AnonymousClass)factory.getRef(_hasAnonymousClass);
	}

	@Override
	public NormalMethod getConstructor() {
		if (_constructor == 0)
			return null;
		if (factory.getIsFiltered(_constructor))
			return null;
		return (NormalMethod)factory.getRef(_constructor);
	}

	@Override
	public void setEnclosingExpression(int _id) {
		if (_hasEnclosingExpression != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasEnclosingExpression" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkExpression)) {
			_hasEnclosingExpression = _id;
			setParentEdge(_hasEnclosingExpression);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setEnclosingExpression(Expression _node) {
		if (_hasEnclosingExpression != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasEnclosingExpression" ));

		_hasEnclosingExpression = _node.getId();
		setParentEdge(_hasEnclosingExpression);
	}

	@Override
	public void addTypeArguments(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkTypeExpression)) {
			if (_hasTypeArguments == null)
				_hasTypeArguments = new EdgeList<TypeExpression>(factory);
			_hasTypeArguments.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addTypeArguments(TypeExpression _node) {
		if (_hasTypeArguments == null)
			_hasTypeArguments = new EdgeList<TypeExpression>(factory);
		_hasTypeArguments.add(_node);
		setParentEdge(_node);
	}

	@Override
	public void setTypeName(int _id) {
		if (_hasTypeName != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasTypeName" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkTypeExpression)) {
			_hasTypeName = _id;
			setParentEdge(_hasTypeName);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setTypeName(TypeExpression _node) {
		if (_hasTypeName != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasTypeName" ));

		_hasTypeName = _node.getId();
		setParentEdge(_hasTypeName);
	}

	@Override
	public void addArguments(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkExpression)) {
			if (_hasArguments == null)
				_hasArguments = new EdgeList<Expression>(factory);
			_hasArguments.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addArguments(Expression _node) {
		if (_hasArguments == null)
			_hasArguments = new EdgeList<Expression>(factory);
		_hasArguments.add(_node);
		setParentEdge(_node);
	}

	@Override
	public void setAnonymousClass(int _id) {
		if (_hasAnonymousClass != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasAnonymousClass" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkAnonymousClass) {
			_hasAnonymousClass = _id;
			setParentEdge(_hasAnonymousClass);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setAnonymousClass(AnonymousClass _node) {
		if (_hasAnonymousClass != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasAnonymousClass" ));

		_hasAnonymousClass = _node.getId();
		setParentEdge(_hasAnonymousClass);
	}

	@Override
	public void setConstructor(int _id) {
		if (_constructor != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","constructor" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkNormalMethod)) {
			_constructor = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setConstructor(NormalMethod _node) {
		if (_constructor != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","constructor" ));

		_constructor = _node.getId();
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


		io.writeInt4(!factory.getIsFiltered(_hasEnclosingExpression) ? _hasEnclosingExpression : 0);

		io.writeInt4(!factory.getIsFiltered(_hasTypeName) ? _hasTypeName : 0);

		io.writeInt4(!factory.getIsFiltered(_hasAnonymousClass) ? _hasAnonymousClass : 0);

		io.writeInt4(!factory.getIsFiltered(_constructor) ? _constructor : 0);

		if (_hasTypeArguments != null) {
			EdgeIterator<TypeExpression> it = getTypeArgumentsIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);

		if (_hasArguments != null) {
			EdgeIterator<Expression> it = getArgumentsIterator();
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

		_hasEnclosingExpression = io.readInt4();
		if (_hasEnclosingExpression != 0)
			setParentEdge(_hasEnclosingExpression);

		_hasTypeName = io.readInt4();
		if (_hasTypeName != 0)
			setParentEdge(_hasTypeName);

		_hasAnonymousClass = io.readInt4();
		if (_hasAnonymousClass != 0)
			setParentEdge(_hasAnonymousClass);

		_constructor = io.readInt4();


		_id = io.readInt4();
		if (_id != 0) {
			_hasTypeArguments = new EdgeList<TypeExpression>(factory);
			while (_id != 0) {
				_hasTypeArguments.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}

		_id = io.readInt4();
		if (_id != 0) {
			_hasArguments = new EdgeList<Expression>(factory);
			while (_id != 0) {
				_hasArguments.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}
	}

}
