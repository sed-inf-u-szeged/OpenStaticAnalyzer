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

package columbus.java.asg.struc;

import columbus.IO;
import columbus.java.asg.*;
import columbus.java.asg.base.BaseImpl;
import columbus.java.asg.base.Base;
import columbus.java.asg.expr.Expression;
import columbus.java.asg.expr.TypeExpression;
import columbus.java.asg.base.Comment;
import columbus.java.asg.expr.Annotation;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.struc.Variable Variable} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class VariableImpl extends BaseImpl implements Variable {

	private static final LoggerHandler logger = new LoggerHandler(VariableImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected EdgeList<Comment> _comments;

	protected EdgeList<Annotation> _hasAnnotations;

	protected Object position;

	protected boolean isCompilerGenerated;

	protected boolean isToolGenerated;

	protected int name;

	protected Object namePosition;

	protected AccessibilityKind accessibility = AccessibilityKind.ackNone;

	protected Object accessibilityPosition;

	protected boolean isStatic;

	protected Object staticPosition;

	protected boolean isFinal;

	protected Object finalPosition;

	protected int _hasType;

	protected boolean isTransient;

	protected Object transientPosition;

	protected boolean isVolatile;

	protected Object volatilePosition;

	protected Object equalSignPosition;

	protected int _hasInitialValue;

	public VariableImpl(int id, Factory factory) {
		super(id, factory);
		position = new Range(factory.getStringTable());
		namePosition = new Range(factory.getStringTable());
		accessibilityPosition = new Range(factory.getStringTable());
		staticPosition = new Range(factory.getStringTable());
		finalPosition = new Range(factory.getStringTable());
		transientPosition = new Range(factory.getStringTable());
		volatilePosition = new Range(factory.getStringTable());
		equalSignPosition = new Range(factory.getStringTable());
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkVariable;
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
	public String getName() {
		return factory.getStringTable().get(name);
	}

	@Override
	public int getNameKey() {
		return name;
	}

	@Override
	public Range getNamePosition() {
		return (Range)namePosition;
	}

	@Override
	public void setName(String _name) {
		name = factory.getStringTable().set(_name);
	}

	@Override
	public void setNamePosition(Range _namePosition) {
		if (factory.getStringTable() == _namePosition.getStringTable())
			namePosition = _namePosition;
		else
			namePosition = new Range(factory.getStringTable(), _namePosition);
	}

	@Override
	public AccessibilityKind getAccessibility() {
		return accessibility;
	}

	@Override
	public Range getAccessibilityPosition() {
		return (Range)accessibilityPosition;
	}

	@Override
	public boolean getIsStatic() {
		return isStatic;
	}

	@Override
	public Range getStaticPosition() {
		return (Range)staticPosition;
	}

	@Override
	public boolean getIsFinal() {
		return isFinal;
	}

	@Override
	public Range getFinalPosition() {
		return (Range)finalPosition;
	}

	@Override
	public void setAccessibility(AccessibilityKind _accessibility) {
		accessibility = _accessibility;
	}

	@Override
	public void setAccessibilityPosition(Range _accessibilityPosition) {
		if (factory.getStringTable() == _accessibilityPosition.getStringTable())
			accessibilityPosition = _accessibilityPosition;
		else
			accessibilityPosition = new Range(factory.getStringTable(), _accessibilityPosition);
	}

	@Override
	public void setIsStatic(boolean _isStatic) {
		isStatic = _isStatic;
	}

	@Override
	public void setStaticPosition(Range _staticPosition) {
		if (factory.getStringTable() == _staticPosition.getStringTable())
			staticPosition = _staticPosition;
		else
			staticPosition = new Range(factory.getStringTable(), _staticPosition);
	}

	@Override
	public void setIsFinal(boolean _isFinal) {
		isFinal = _isFinal;
	}

	@Override
	public void setFinalPosition(Range _finalPosition) {
		if (factory.getStringTable() == _finalPosition.getStringTable())
			finalPosition = _finalPosition;
		else
			finalPosition = new Range(factory.getStringTable(), _finalPosition);
	}

	@Override
	public boolean getIsTransient() {
		return isTransient;
	}

	@Override
	public Range getTransientPosition() {
		return (Range)transientPosition;
	}

	@Override
	public boolean getIsVolatile() {
		return isVolatile;
	}

	@Override
	public Range getVolatilePosition() {
		return (Range)volatilePosition;
	}

	@Override
	public Range getEqualSignPosition() {
		return (Range)equalSignPosition;
	}

	@Override
	public void setIsTransient(boolean _isTransient) {
		isTransient = _isTransient;
	}

	@Override
	public void setTransientPosition(Range _transientPosition) {
		if (factory.getStringTable() == _transientPosition.getStringTable())
			transientPosition = _transientPosition;
		else
			transientPosition = new Range(factory.getStringTable(), _transientPosition);
	}

	@Override
	public void setIsVolatile(boolean _isVolatile) {
		isVolatile = _isVolatile;
	}

	@Override
	public void setVolatilePosition(Range _volatilePosition) {
		if (factory.getStringTable() == _volatilePosition.getStringTable())
			volatilePosition = _volatilePosition;
		else
			volatilePosition = new Range(factory.getStringTable(), _volatilePosition);
	}

	@Override
	public void setEqualSignPosition(Range _equalSignPosition) {
		if (factory.getStringTable() == _equalSignPosition.getStringTable())
			equalSignPosition = _equalSignPosition;
		else
			equalSignPosition = new Range(factory.getStringTable(), _equalSignPosition);
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
	public EdgeIterator<Annotation> getAnnotationsIterator() {
		if (_hasAnnotations == null)
			return EdgeList.<Annotation>emptyList().iterator();
		else
			return _hasAnnotations.iterator();
	}

	@Override
	public boolean getAnnotationsIsEmpty() {
		if (_hasAnnotations == null)
			return true;
		else
			return _hasAnnotations.isEmpty();
	}

	@Override
	public int getAnnotationsSize() {
		if (_hasAnnotations == null)
			return 0;
		else
			return _hasAnnotations.size();
	}

	@Override
	public void addAnnotations(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkAnnotation)) {
			if (_hasAnnotations == null)
				_hasAnnotations = new EdgeList<Annotation>(factory);
			_hasAnnotations.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addAnnotations(Annotation _node) {
		if (_hasAnnotations == null)
			_hasAnnotations = new EdgeList<Annotation>(factory);
		_hasAnnotations.add(_node);
		setParentEdge(_node);
	}

	@Override
	public TypeExpression getType() {
		if (_hasType == 0)
			return null;
		if (factory.getIsFiltered(_hasType))
			return null;
		return (TypeExpression)factory.getRef(_hasType);
	}

	@Override
	public void setType(int _id) {
		if (_hasType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasType" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkTypeExpression)) {
			_hasType = _id;
			setParentEdge(_hasType);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setType(TypeExpression _node) {
		if (_hasType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasType" ));

		_hasType = _node.getId();
		setParentEdge(_hasType);
	}

	@Override
	public Expression getInitialValue() {
		if (_hasInitialValue == 0)
			return null;
		if (factory.getIsFiltered(_hasInitialValue))
			return null;
		return (Expression)factory.getRef(_hasInitialValue);
	}

	@Override
	public void setInitialValue(int _id) {
		if (_hasInitialValue != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasInitialValue" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkExpression)) {
			_hasInitialValue = _id;
			setParentEdge(_hasInitialValue);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setInitialValue(Expression _node) {
		if (_hasInitialValue != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasInitialValue" ));

		_hasInitialValue = _node.getId();
		setParentEdge(_hasInitialValue);
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

		if (_hasAnnotations != null) {
			EdgeIterator<Annotation> it = getAnnotationsIterator();
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

		io.writeInt4(name);
		io.writeInt4(((Range)namePosition).getPathKey());
		io.writeInt4(((Range)namePosition).getLine());
		io.writeInt4(((Range)namePosition).getCol());
		io.writeInt4(((Range)namePosition).getEndLine());
		io.writeInt4(((Range)namePosition).getEndCol());
		io.writeInt4(((Range)namePosition).getWideLine());
		io.writeInt4(((Range)namePosition).getWideCol());
		io.writeInt4(((Range)namePosition).getWideEndLine());
		io.writeInt4(((Range)namePosition).getWideEndCol());
		{
			byte boolValues = 0;
			boolValues <<= 1;
			if (isStatic) 
				boolValues |= 1;
			boolValues <<= 1;
			if (isFinal) 
				boolValues |= 1;
			io.writeByte1(boolValues);
		}
		io.writeUByte1(accessibility.ordinal());
		io.writeInt4(((Range)accessibilityPosition).getPathKey());
		io.writeInt4(((Range)accessibilityPosition).getLine());
		io.writeInt4(((Range)accessibilityPosition).getCol());
		io.writeInt4(((Range)accessibilityPosition).getEndLine());
		io.writeInt4(((Range)accessibilityPosition).getEndCol());
		io.writeInt4(((Range)accessibilityPosition).getWideLine());
		io.writeInt4(((Range)accessibilityPosition).getWideCol());
		io.writeInt4(((Range)accessibilityPosition).getWideEndLine());
		io.writeInt4(((Range)accessibilityPosition).getWideEndCol());
		io.writeInt4(((Range)staticPosition).getPathKey());
		io.writeInt4(((Range)staticPosition).getLine());
		io.writeInt4(((Range)staticPosition).getCol());
		io.writeInt4(((Range)staticPosition).getEndLine());
		io.writeInt4(((Range)staticPosition).getEndCol());
		io.writeInt4(((Range)staticPosition).getWideLine());
		io.writeInt4(((Range)staticPosition).getWideCol());
		io.writeInt4(((Range)staticPosition).getWideEndLine());
		io.writeInt4(((Range)staticPosition).getWideEndCol());
		io.writeInt4(((Range)finalPosition).getPathKey());
		io.writeInt4(((Range)finalPosition).getLine());
		io.writeInt4(((Range)finalPosition).getCol());
		io.writeInt4(((Range)finalPosition).getEndLine());
		io.writeInt4(((Range)finalPosition).getEndCol());
		io.writeInt4(((Range)finalPosition).getWideLine());
		io.writeInt4(((Range)finalPosition).getWideCol());
		io.writeInt4(((Range)finalPosition).getWideEndLine());
		io.writeInt4(((Range)finalPosition).getWideEndCol());


		io.writeInt4(!factory.getIsFiltered(_hasType) ? _hasType : 0);
		{
			byte boolValues = 0;
			boolValues <<= 1;
			if (isTransient) 
				boolValues |= 1;
			boolValues <<= 1;
			if (isVolatile) 
				boolValues |= 1;
			io.writeByte1(boolValues);
		}
		io.writeInt4(((Range)transientPosition).getPathKey());
		io.writeInt4(((Range)transientPosition).getLine());
		io.writeInt4(((Range)transientPosition).getCol());
		io.writeInt4(((Range)transientPosition).getEndLine());
		io.writeInt4(((Range)transientPosition).getEndCol());
		io.writeInt4(((Range)transientPosition).getWideLine());
		io.writeInt4(((Range)transientPosition).getWideCol());
		io.writeInt4(((Range)transientPosition).getWideEndLine());
		io.writeInt4(((Range)transientPosition).getWideEndCol());
		io.writeInt4(((Range)volatilePosition).getPathKey());
		io.writeInt4(((Range)volatilePosition).getLine());
		io.writeInt4(((Range)volatilePosition).getCol());
		io.writeInt4(((Range)volatilePosition).getEndLine());
		io.writeInt4(((Range)volatilePosition).getEndCol());
		io.writeInt4(((Range)volatilePosition).getWideLine());
		io.writeInt4(((Range)volatilePosition).getWideCol());
		io.writeInt4(((Range)volatilePosition).getWideEndLine());
		io.writeInt4(((Range)volatilePosition).getWideEndCol());
		io.writeInt4(((Range)equalSignPosition).getPathKey());
		io.writeInt4(((Range)equalSignPosition).getLine());
		io.writeInt4(((Range)equalSignPosition).getCol());
		io.writeInt4(((Range)equalSignPosition).getEndLine());
		io.writeInt4(((Range)equalSignPosition).getEndCol());
		io.writeInt4(((Range)equalSignPosition).getWideLine());
		io.writeInt4(((Range)equalSignPosition).getWideCol());
		io.writeInt4(((Range)equalSignPosition).getWideEndLine());
		io.writeInt4(((Range)equalSignPosition).getWideEndCol());


		io.writeInt4(!factory.getIsFiltered(_hasInitialValue) ? _hasInitialValue : 0);
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


		_id = io.readInt4();
		if (_id != 0) {
			_hasAnnotations = new EdgeList<Annotation>(factory);
			while (_id != 0) {
				_hasAnnotations.add(_id);
				setParentEdge(_id);
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


		name = io.readInt4();
		((Range)namePosition).setPathKey(io.readInt4());
		((Range)namePosition).setLine(io.readInt4());
		((Range)namePosition).setCol(io.readInt4());
		((Range)namePosition).setEndLine(io.readInt4());
		((Range)namePosition).setEndCol(io.readInt4());
		((Range)namePosition).setWideLine(io.readInt4());
		((Range)namePosition).setWideCol(io.readInt4());
		((Range)namePosition).setWideEndLine(io.readInt4());
		((Range)namePosition).setWideEndCol(io.readInt4());
		{
			byte boolValues = io.readByte1();
			isFinal = (boolValues & 1) != 0;
			boolValues >>>= 1;
			isStatic = (boolValues & 1) != 0;
			boolValues >>>= 1;
		}

		accessibility = AccessibilityKind.values()[io.readUByte1()];
		((Range)accessibilityPosition).setPathKey(io.readInt4());
		((Range)accessibilityPosition).setLine(io.readInt4());
		((Range)accessibilityPosition).setCol(io.readInt4());
		((Range)accessibilityPosition).setEndLine(io.readInt4());
		((Range)accessibilityPosition).setEndCol(io.readInt4());
		((Range)accessibilityPosition).setWideLine(io.readInt4());
		((Range)accessibilityPosition).setWideCol(io.readInt4());
		((Range)accessibilityPosition).setWideEndLine(io.readInt4());
		((Range)accessibilityPosition).setWideEndCol(io.readInt4());
		((Range)staticPosition).setPathKey(io.readInt4());
		((Range)staticPosition).setLine(io.readInt4());
		((Range)staticPosition).setCol(io.readInt4());
		((Range)staticPosition).setEndLine(io.readInt4());
		((Range)staticPosition).setEndCol(io.readInt4());
		((Range)staticPosition).setWideLine(io.readInt4());
		((Range)staticPosition).setWideCol(io.readInt4());
		((Range)staticPosition).setWideEndLine(io.readInt4());
		((Range)staticPosition).setWideEndCol(io.readInt4());
		((Range)finalPosition).setPathKey(io.readInt4());
		((Range)finalPosition).setLine(io.readInt4());
		((Range)finalPosition).setCol(io.readInt4());
		((Range)finalPosition).setEndLine(io.readInt4());
		((Range)finalPosition).setEndCol(io.readInt4());
		((Range)finalPosition).setWideLine(io.readInt4());
		((Range)finalPosition).setWideCol(io.readInt4());
		((Range)finalPosition).setWideEndLine(io.readInt4());
		((Range)finalPosition).setWideEndCol(io.readInt4());

		_hasType = io.readInt4();
		if (_hasType != 0)
			setParentEdge(_hasType);
		{
			byte boolValues = io.readByte1();
			isVolatile = (boolValues & 1) != 0;
			boolValues >>>= 1;
			isTransient = (boolValues & 1) != 0;
			boolValues >>>= 1;
		}

		((Range)transientPosition).setPathKey(io.readInt4());
		((Range)transientPosition).setLine(io.readInt4());
		((Range)transientPosition).setCol(io.readInt4());
		((Range)transientPosition).setEndLine(io.readInt4());
		((Range)transientPosition).setEndCol(io.readInt4());
		((Range)transientPosition).setWideLine(io.readInt4());
		((Range)transientPosition).setWideCol(io.readInt4());
		((Range)transientPosition).setWideEndLine(io.readInt4());
		((Range)transientPosition).setWideEndCol(io.readInt4());
		((Range)volatilePosition).setPathKey(io.readInt4());
		((Range)volatilePosition).setLine(io.readInt4());
		((Range)volatilePosition).setCol(io.readInt4());
		((Range)volatilePosition).setEndLine(io.readInt4());
		((Range)volatilePosition).setEndCol(io.readInt4());
		((Range)volatilePosition).setWideLine(io.readInt4());
		((Range)volatilePosition).setWideCol(io.readInt4());
		((Range)volatilePosition).setWideEndLine(io.readInt4());
		((Range)volatilePosition).setWideEndCol(io.readInt4());
		((Range)equalSignPosition).setPathKey(io.readInt4());
		((Range)equalSignPosition).setLine(io.readInt4());
		((Range)equalSignPosition).setCol(io.readInt4());
		((Range)equalSignPosition).setEndLine(io.readInt4());
		((Range)equalSignPosition).setEndCol(io.readInt4());
		((Range)equalSignPosition).setWideLine(io.readInt4());
		((Range)equalSignPosition).setWideCol(io.readInt4());
		((Range)equalSignPosition).setWideEndLine(io.readInt4());
		((Range)equalSignPosition).setWideEndCol(io.readInt4());

		_hasInitialValue = io.readInt4();
		if (_hasInitialValue != 0)
			setParentEdge(_hasInitialValue);
	}

}
