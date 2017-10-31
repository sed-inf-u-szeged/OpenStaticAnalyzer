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
import columbus.java.asg.base.Comment;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.statm.Break Break} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class BreakImpl extends BaseImpl implements Break {

	private static final LoggerHandler logger = new LoggerHandler(BreakImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected EdgeList<Comment> _comments;

	protected Object position;

	protected boolean isCompilerGenerated;

	protected boolean isToolGenerated;

	protected int label;

	protected Object labelPosition;

	protected int _target;

	public BreakImpl(int id, Factory factory) {
		super(id, factory);
		position = new Range(factory.getStringTable());
		labelPosition = new Range(factory.getStringTable());
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkBreak;
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
	public String getLabel() {
		return factory.getStringTable().get(label);
	}

	@Override
	public int getLabelKey() {
		return label;
	}

	@Override
	public Range getLabelPosition() {
		return (Range)labelPosition;
	}

	@Override
	public void setLabel(String _label) {
		label = factory.getStringTable().set(_label);
	}

	@Override
	public void setLabelPosition(Range _labelPosition) {
		if (factory.getStringTable() == _labelPosition.getStringTable())
			labelPosition = _labelPosition;
		else
			labelPosition = new Range(factory.getStringTable(), _labelPosition);
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
	public Statement getTarget() {
		if (_target == 0)
			return null;
		if (factory.getIsFiltered(_target))
			return null;
		return (Statement)factory.getRef(_target);
	}

	@Override
	public void setTarget(int _id) {
		if (_target != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","target" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkStatement)) {
			_target = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setTarget(Statement _node) {
		if (_target != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","target" ));

		_target = _node.getId();
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

		io.writeInt4(label);
		io.writeInt4(((Range)labelPosition).getPathKey());
		io.writeInt4(((Range)labelPosition).getLine());
		io.writeInt4(((Range)labelPosition).getCol());
		io.writeInt4(((Range)labelPosition).getEndLine());
		io.writeInt4(((Range)labelPosition).getEndCol());
		io.writeInt4(((Range)labelPosition).getWideLine());
		io.writeInt4(((Range)labelPosition).getWideCol());
		io.writeInt4(((Range)labelPosition).getWideEndLine());
		io.writeInt4(((Range)labelPosition).getWideEndCol());


		io.writeInt4(!factory.getIsFiltered(_target) ? _target : 0);
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


		label = io.readInt4();
		((Range)labelPosition).setPathKey(io.readInt4());
		((Range)labelPosition).setLine(io.readInt4());
		((Range)labelPosition).setCol(io.readInt4());
		((Range)labelPosition).setEndLine(io.readInt4());
		((Range)labelPosition).setEndCol(io.readInt4());
		((Range)labelPosition).setWideLine(io.readInt4());
		((Range)labelPosition).setWideCol(io.readInt4());
		((Range)labelPosition).setWideEndLine(io.readInt4());
		((Range)labelPosition).setWideEndCol(io.readInt4());

		_target = io.readInt4();
	}

}
