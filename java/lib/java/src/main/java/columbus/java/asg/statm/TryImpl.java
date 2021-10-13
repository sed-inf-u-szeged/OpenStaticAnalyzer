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
import columbus.java.asg.base.Comment;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.statm.Try Try} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class TryImpl extends BaseImpl implements Try {

	@SuppressWarnings("unused")
	private static final LoggerHandler logger = new LoggerHandler(TryImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected EdgeList<Comment> _comments;

	protected Object position;

	protected boolean isCompilerGenerated;

	protected boolean isToolGenerated;

	protected Object resourceLeftParenPosition;

	protected Object resourceRightParenPosition;

	protected Object finallyPosition;

	protected EdgeList<Base> _hasResources;

	protected int _hasBlock;

	protected EdgeList<Handler> _hasHandlers;

	protected int _hasFinallyBlock;

	public TryImpl(int id, Factory factory) {
		super(id, factory);
		position = new Range(factory.getStringTable());
		resourceLeftParenPosition = new Range(factory.getStringTable());
		resourceRightParenPosition = new Range(factory.getStringTable());
		finallyPosition = new Range(factory.getStringTable());
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkTry;
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
	public Range getResourceLeftParenPosition() {
		return (Range)resourceLeftParenPosition;
	}

	@Override
	public Range getResourceRightParenPosition() {
		return (Range)resourceRightParenPosition;
	}

	@Override
	public Range getFinallyPosition() {
		return (Range)finallyPosition;
	}

	@Override
	public void setResourceLeftParenPosition(Range _resourceLeftParenPosition) {
		if (factory.getStringTable() == _resourceLeftParenPosition.getStringTable())
			resourceLeftParenPosition = _resourceLeftParenPosition;
		else
			resourceLeftParenPosition = new Range(factory.getStringTable(), _resourceLeftParenPosition);
	}

	@Override
	public void setResourceRightParenPosition(Range _resourceRightParenPosition) {
		if (factory.getStringTable() == _resourceRightParenPosition.getStringTable())
			resourceRightParenPosition = _resourceRightParenPosition;
		else
			resourceRightParenPosition = new Range(factory.getStringTable(), _resourceRightParenPosition);
	}

	@Override
	public void setFinallyPosition(Range _finallyPosition) {
		if (factory.getStringTable() == _finallyPosition.getStringTable())
			finallyPosition = _finallyPosition;
		else
			finallyPosition = new Range(factory.getStringTable(), _finallyPosition);
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
	public EdgeIterator<Base> getResourcesIterator() {
		if (_hasResources == null)
			return EdgeList.<Base>emptyList().iterator();
		else
			return _hasResources.iterator();
	}

	@Override
	public boolean getResourcesIsEmpty() {
		if (_hasResources == null)
			return true;
		else
			return _hasResources.isEmpty();
	}

	@Override
	public int getResourcesSize() {
		if (_hasResources == null)
			return 0;
		else
			return _hasResources.size();
	}

	@Override
	public Block getBlock() {
		if (_hasBlock == 0)
			return null;
		if (factory.getIsFiltered(_hasBlock))
			return null;
		return (Block)factory.getRef(_hasBlock);
	}

	@Override
	public EdgeIterator<Handler> getHandlersIterator() {
		if (_hasHandlers == null)
			return EdgeList.<Handler>emptyList().iterator();
		else
			return _hasHandlers.iterator();
	}

	@Override
	public boolean getHandlersIsEmpty() {
		if (_hasHandlers == null)
			return true;
		else
			return _hasHandlers.isEmpty();
	}

	@Override
	public int getHandlersSize() {
		if (_hasHandlers == null)
			return 0;
		else
			return _hasHandlers.size();
	}

	@Override
	public Block getFinallyBlock() {
		if (_hasFinallyBlock == 0)
			return null;
		if (factory.getIsFiltered(_hasFinallyBlock))
			return null;
		return (Block)factory.getRef(_hasFinallyBlock);
	}

	@Override
	public void addResources(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkVariable || Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkExpression)) {
			if (_hasResources == null)
				_hasResources = new EdgeList<Base>(factory);
			_hasResources.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addResources(Base _node) {
		if (_node.getNodeKind() == NodeKind.ndkVariable || Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkExpression)) {
			if (_hasResources == null)
				_hasResources = new EdgeList<Base>(factory);
			_hasResources.add(_node);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_node);
	}

	@Override
	public void setBlock(int _id) {
		if (_hasBlock != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasBlock" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkBlock) {
			_hasBlock = _id;
			setParentEdge(_hasBlock);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setBlock(Block _node) {
		if (_hasBlock != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasBlock" ));

		_hasBlock = _node.getId();
		setParentEdge(_hasBlock);
	}

	@Override
	public void addHandlers(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkHandler) {
			if (_hasHandlers == null)
				_hasHandlers = new EdgeList<Handler>(factory);
			_hasHandlers.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addHandlers(Handler _node) {
		if (_hasHandlers == null)
			_hasHandlers = new EdgeList<Handler>(factory);
		_hasHandlers.add(_node);
		setParentEdge(_node);
	}

	@Override
	public void setFinallyBlock(int _id) {
		if (_hasFinallyBlock != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasFinallyBlock" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkBlock) {
			_hasFinallyBlock = _id;
			setParentEdge(_hasFinallyBlock);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setFinallyBlock(Block _node) {
		if (_hasFinallyBlock != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasFinallyBlock" ));

		_hasFinallyBlock = _node.getId();
		setParentEdge(_hasFinallyBlock);
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

		io.writeInt4(((Range)resourceLeftParenPosition).getPathKey());
		io.writeInt4(((Range)resourceLeftParenPosition).getLine());
		io.writeInt4(((Range)resourceLeftParenPosition).getCol());
		io.writeInt4(((Range)resourceLeftParenPosition).getEndLine());
		io.writeInt4(((Range)resourceLeftParenPosition).getEndCol());
		io.writeInt4(((Range)resourceLeftParenPosition).getWideLine());
		io.writeInt4(((Range)resourceLeftParenPosition).getWideCol());
		io.writeInt4(((Range)resourceLeftParenPosition).getWideEndLine());
		io.writeInt4(((Range)resourceLeftParenPosition).getWideEndCol());
		io.writeInt4(((Range)resourceRightParenPosition).getPathKey());
		io.writeInt4(((Range)resourceRightParenPosition).getLine());
		io.writeInt4(((Range)resourceRightParenPosition).getCol());
		io.writeInt4(((Range)resourceRightParenPosition).getEndLine());
		io.writeInt4(((Range)resourceRightParenPosition).getEndCol());
		io.writeInt4(((Range)resourceRightParenPosition).getWideLine());
		io.writeInt4(((Range)resourceRightParenPosition).getWideCol());
		io.writeInt4(((Range)resourceRightParenPosition).getWideEndLine());
		io.writeInt4(((Range)resourceRightParenPosition).getWideEndCol());
		io.writeInt4(((Range)finallyPosition).getPathKey());
		io.writeInt4(((Range)finallyPosition).getLine());
		io.writeInt4(((Range)finallyPosition).getCol());
		io.writeInt4(((Range)finallyPosition).getEndLine());
		io.writeInt4(((Range)finallyPosition).getEndCol());
		io.writeInt4(((Range)finallyPosition).getWideLine());
		io.writeInt4(((Range)finallyPosition).getWideCol());
		io.writeInt4(((Range)finallyPosition).getWideEndLine());
		io.writeInt4(((Range)finallyPosition).getWideEndCol());


		io.writeInt4(!factory.getIsFiltered(_hasBlock) ? _hasBlock : 0);

		io.writeInt4(!factory.getIsFiltered(_hasFinallyBlock) ? _hasFinallyBlock : 0);

		if (_hasResources != null) {
			EdgeIterator<Base> it = getResourcesIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);

		if (_hasHandlers != null) {
			EdgeIterator<Handler> it = getHandlersIterator();
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


		((Range)resourceLeftParenPosition).setPathKey(io.readInt4());
		((Range)resourceLeftParenPosition).setLine(io.readInt4());
		((Range)resourceLeftParenPosition).setCol(io.readInt4());
		((Range)resourceLeftParenPosition).setEndLine(io.readInt4());
		((Range)resourceLeftParenPosition).setEndCol(io.readInt4());
		((Range)resourceLeftParenPosition).setWideLine(io.readInt4());
		((Range)resourceLeftParenPosition).setWideCol(io.readInt4());
		((Range)resourceLeftParenPosition).setWideEndLine(io.readInt4());
		((Range)resourceLeftParenPosition).setWideEndCol(io.readInt4());
		((Range)resourceRightParenPosition).setPathKey(io.readInt4());
		((Range)resourceRightParenPosition).setLine(io.readInt4());
		((Range)resourceRightParenPosition).setCol(io.readInt4());
		((Range)resourceRightParenPosition).setEndLine(io.readInt4());
		((Range)resourceRightParenPosition).setEndCol(io.readInt4());
		((Range)resourceRightParenPosition).setWideLine(io.readInt4());
		((Range)resourceRightParenPosition).setWideCol(io.readInt4());
		((Range)resourceRightParenPosition).setWideEndLine(io.readInt4());
		((Range)resourceRightParenPosition).setWideEndCol(io.readInt4());
		((Range)finallyPosition).setPathKey(io.readInt4());
		((Range)finallyPosition).setLine(io.readInt4());
		((Range)finallyPosition).setCol(io.readInt4());
		((Range)finallyPosition).setEndLine(io.readInt4());
		((Range)finallyPosition).setEndCol(io.readInt4());
		((Range)finallyPosition).setWideLine(io.readInt4());
		((Range)finallyPosition).setWideCol(io.readInt4());
		((Range)finallyPosition).setWideEndLine(io.readInt4());
		((Range)finallyPosition).setWideEndCol(io.readInt4());

		_hasBlock = io.readInt4();
		if (_hasBlock != 0)
			setParentEdge(_hasBlock);

		_hasFinallyBlock = io.readInt4();
		if (_hasFinallyBlock != 0)
			setParentEdge(_hasFinallyBlock);


		_id = io.readInt4();
		if (_id != 0) {
			_hasResources = new EdgeList<Base>(factory);
			while (_id != 0) {
				_hasResources.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}

		_id = io.readInt4();
		if (_id != 0) {
			_hasHandlers = new EdgeList<Handler>(factory);
			while (_id != 0) {
				_hasHandlers.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}
	}

}
