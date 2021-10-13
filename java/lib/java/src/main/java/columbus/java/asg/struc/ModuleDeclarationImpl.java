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

package columbus.java.asg.struc;

import columbus.IO;
import columbus.java.asg.*;
import columbus.java.asg.base.BaseImpl;
import columbus.java.asg.base.Base;
import columbus.java.asg.expr.Expression;
import columbus.java.asg.module.ModuleDirective;
import columbus.java.asg.type.ModuleType;
import columbus.java.asg.base.Comment;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.struc.ModuleDeclaration ModuleDeclaration} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class ModuleDeclarationImpl extends BaseImpl implements ModuleDeclaration {

	@SuppressWarnings("unused")
	private static final LoggerHandler logger = new LoggerHandler(ModuleDeclarationImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected EdgeList<Comment> _comments;

	protected Object position;

	protected boolean isCompilerGenerated;

	protected boolean isToolGenerated;

	protected ModuleKind moduleKind = ModuleKind.mkOpen;

	protected int _hasName;

	protected EdgeList<ModuleDirective> _hasDirectives;

	protected int _moduleType;

	protected int _refersTo;

	public ModuleDeclarationImpl(int id, Factory factory) {
		super(id, factory);
		position = new Range(factory.getStringTable());
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkModuleDeclaration;
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
	public ModuleKind getModuleKind() {
		return moduleKind;
	}

	@Override
	public void setModuleKind(ModuleKind _moduleKind) {
		moduleKind = _moduleKind;
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
	public Expression getName() {
		if (_hasName == 0)
			return null;
		if (factory.getIsFiltered(_hasName))
			return null;
		return (Expression)factory.getRef(_hasName);
	}

	@Override
	public EdgeIterator<ModuleDirective> getDirectivesIterator() {
		if (_hasDirectives == null)
			return EdgeList.<ModuleDirective>emptyList().iterator();
		else
			return _hasDirectives.iterator();
	}

	@Override
	public boolean getDirectivesIsEmpty() {
		if (_hasDirectives == null)
			return true;
		else
			return _hasDirectives.isEmpty();
	}

	@Override
	public int getDirectivesSize() {
		if (_hasDirectives == null)
			return 0;
		else
			return _hasDirectives.size();
	}

	@Override
	public ModuleType getModuleType() {
		if (_moduleType == 0)
			return null;
		if (factory.getIsFiltered(_moduleType))
			return null;
		return (ModuleType)factory.getRef(_moduleType);
	}

	@Override
	public Module getRefersTo() {
		if (_refersTo == 0)
			return null;
		if (factory.getIsFiltered(_refersTo))
			return null;
		return (Module)factory.getRef(_refersTo);
	}

	@Override
	public void setName(int _id) {
		if (_hasName != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasName" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkExpression)) {
			_hasName = _id;
			setParentEdge(_hasName);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setName(Expression _node) {
		if (_hasName != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasName" ));

		_hasName = _node.getId();
		setParentEdge(_hasName);
	}

	@Override
	public void addDirectives(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkModuleDirective)) {
			if (_hasDirectives == null)
				_hasDirectives = new EdgeList<ModuleDirective>(factory);
			_hasDirectives.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addDirectives(ModuleDirective _node) {
		if (_hasDirectives == null)
			_hasDirectives = new EdgeList<ModuleDirective>(factory);
		_hasDirectives.add(_node);
		setParentEdge(_node);
	}

	@Override
	public void setModuleType(int _id) {
		if (_moduleType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","moduleType" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkModuleType) {
			_moduleType = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setModuleType(ModuleType _node) {
		if (_moduleType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","moduleType" ));

		_moduleType = _node.getId();
	}

	@Override
	public void setRefersTo(int _id) {
		if (_refersTo != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","refersTo" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkModule) {
			_refersTo = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setRefersTo(Module _node) {
		if (_refersTo != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","refersTo" ));

		_refersTo = _node.getId();
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

		io.writeUByte1(moduleKind.ordinal());


		io.writeInt4(!factory.getIsFiltered(_hasName) ? _hasName : 0);

		io.writeInt4(!factory.getIsFiltered(_moduleType) ? _moduleType : 0);

		io.writeInt4(!factory.getIsFiltered(_refersTo) ? _refersTo : 0);

		if (_hasDirectives != null) {
			EdgeIterator<ModuleDirective> it = getDirectivesIterator();
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


		moduleKind = ModuleKind.values()[io.readUByte1()];

		_hasName = io.readInt4();
		if (_hasName != 0)
			setParentEdge(_hasName);

		_moduleType = io.readInt4();

		_refersTo = io.readInt4();


		_id = io.readInt4();
		if (_id != 0) {
			_hasDirectives = new EdgeList<ModuleDirective>(factory);
			while (_id != 0) {
				_hasDirectives.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}
	}

}
