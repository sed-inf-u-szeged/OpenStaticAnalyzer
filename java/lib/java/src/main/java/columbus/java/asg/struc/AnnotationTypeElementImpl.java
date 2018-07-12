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
import columbus.java.asg.expr.TypeExpression;
import columbus.java.asg.type.MethodType;
import columbus.java.asg.base.Comment;
import columbus.java.asg.expr.Annotation;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.struc.AnnotationTypeElement AnnotationTypeElement} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class AnnotationTypeElementImpl extends BaseImpl implements AnnotationTypeElement {

	private static final LoggerHandler logger = new LoggerHandler(AnnotationTypeElementImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
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

	protected boolean isAbstract;

	protected Object abstractPosition;

	protected boolean isStrictfp;

	protected Object strictfpPosition;

	protected Object parametersStartPosition;

	protected Object parametersEndPosition;

	protected int _hasReturnType;

	protected int _methodType;

	protected EdgeList<MethodDeclaration> _overrides;

	protected Object defaultPosition;

	protected int _hasDefaultValue;

	public AnnotationTypeElementImpl(int id, Factory factory) {
		super(id, factory);
		position = new Range(factory.getStringTable());
		namePosition = new Range(factory.getStringTable());
		accessibilityPosition = new Range(factory.getStringTable());
		staticPosition = new Range(factory.getStringTable());
		finalPosition = new Range(factory.getStringTable());
		abstractPosition = new Range(factory.getStringTable());
		strictfpPosition = new Range(factory.getStringTable());
		parametersStartPosition = new Range(factory.getStringTable());
		parametersEndPosition = new Range(factory.getStringTable());
		defaultPosition = new Range(factory.getStringTable());
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkAnnotationTypeElement;
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
	public boolean getIsAbstract() {
		return isAbstract;
	}

	@Override
	public Range getAbstractPosition() {
		return (Range)abstractPosition;
	}

	@Override
	public boolean getIsStrictfp() {
		return isStrictfp;
	}

	@Override
	public Range getStrictfpPosition() {
		return (Range)strictfpPosition;
	}

	@Override
	public Range getParametersStartPosition() {
		return (Range)parametersStartPosition;
	}

	@Override
	public Range getParametersEndPosition() {
		return (Range)parametersEndPosition;
	}

	@Override
	public void setIsAbstract(boolean _isAbstract) {
		isAbstract = _isAbstract;
	}

	@Override
	public void setAbstractPosition(Range _abstractPosition) {
		if (factory.getStringTable() == _abstractPosition.getStringTable())
			abstractPosition = _abstractPosition;
		else
			abstractPosition = new Range(factory.getStringTable(), _abstractPosition);
	}

	@Override
	public void setIsStrictfp(boolean _isStrictfp) {
		isStrictfp = _isStrictfp;
	}

	@Override
	public void setStrictfpPosition(Range _strictfpPosition) {
		if (factory.getStringTable() == _strictfpPosition.getStringTable())
			strictfpPosition = _strictfpPosition;
		else
			strictfpPosition = new Range(factory.getStringTable(), _strictfpPosition);
	}

	@Override
	public void setParametersStartPosition(Range _parametersStartPosition) {
		if (factory.getStringTable() == _parametersStartPosition.getStringTable())
			parametersStartPosition = _parametersStartPosition;
		else
			parametersStartPosition = new Range(factory.getStringTable(), _parametersStartPosition);
	}

	@Override
	public void setParametersEndPosition(Range _parametersEndPosition) {
		if (factory.getStringTable() == _parametersEndPosition.getStringTable())
			parametersEndPosition = _parametersEndPosition;
		else
			parametersEndPosition = new Range(factory.getStringTable(), _parametersEndPosition);
	}

	@Override
	public Range getDefaultPosition() {
		return (Range)defaultPosition;
	}

	@Override
	public void setDefaultPosition(Range _defaultPosition) {
		if (factory.getStringTable() == _defaultPosition.getStringTable())
			defaultPosition = _defaultPosition;
		else
			defaultPosition = new Range(factory.getStringTable(), _defaultPosition);
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
	public TypeExpression getReturnType() {
		if (_hasReturnType == 0)
			return null;
		if (factory.getIsFiltered(_hasReturnType))
			return null;
		return (TypeExpression)factory.getRef(_hasReturnType);
	}

	@Override
	public MethodType getMethodType() {
		if (_methodType == 0)
			return null;
		if (factory.getIsFiltered(_methodType))
			return null;
		return (MethodType)factory.getRef(_methodType);
	}

	@Override
	public EdgeIterator<MethodDeclaration> getOverridesIterator() {
		if (_overrides == null)
			return EdgeList.<MethodDeclaration>emptyList().iterator();
		else
			return _overrides.iterator();
	}

	@Override
	public boolean getOverridesIsEmpty() {
		if (_overrides == null)
			return true;
		else
			return _overrides.isEmpty();
	}

	@Override
	public int getOverridesSize() {
		if (_overrides == null)
			return 0;
		else
			return _overrides.size();
	}

	@Override
	public void setReturnType(int _id) {
		if (_hasReturnType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasReturnType" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkTypeExpression)) {
			_hasReturnType = _id;
			setParentEdge(_hasReturnType);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setReturnType(TypeExpression _node) {
		if (_hasReturnType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasReturnType" ));

		_hasReturnType = _node.getId();
		setParentEdge(_hasReturnType);
	}

	@Override
	public void setMethodType(int _id) {
		if (_methodType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","methodType" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkMethodType) {
			_methodType = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setMethodType(MethodType _node) {
		if (_methodType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","methodType" ));

		_methodType = _node.getId();
	}

	@Override
	public void addOverrides(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkMethodDeclaration)) {
			if (_overrides == null)
				_overrides = new EdgeList<MethodDeclaration>(factory);
			_overrides.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void addOverrides(MethodDeclaration _node) {
		if (_overrides == null)
			_overrides = new EdgeList<MethodDeclaration>(factory);
		_overrides.add(_node);
	}

	@Override
	public Expression getDefaultValue() {
		if (_hasDefaultValue == 0)
			return null;
		if (factory.getIsFiltered(_hasDefaultValue))
			return null;
		return (Expression)factory.getRef(_hasDefaultValue);
	}

	@Override
	public void setDefaultValue(int _id) {
		if (_hasDefaultValue != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasDefaultValue" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkExpression)) {
			_hasDefaultValue = _id;
			setParentEdge(_hasDefaultValue);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setDefaultValue(Expression _node) {
		if (_hasDefaultValue != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasDefaultValue" ));

		_hasDefaultValue = _node.getId();
		setParentEdge(_hasDefaultValue);
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
		{
			byte boolValues = 0;
			boolValues <<= 1;
			if (isAbstract) 
				boolValues |= 1;
			boolValues <<= 1;
			if (isStrictfp) 
				boolValues |= 1;
			io.writeByte1(boolValues);
		}
		io.writeInt4(((Range)abstractPosition).getPathKey());
		io.writeInt4(((Range)abstractPosition).getLine());
		io.writeInt4(((Range)abstractPosition).getCol());
		io.writeInt4(((Range)abstractPosition).getEndLine());
		io.writeInt4(((Range)abstractPosition).getEndCol());
		io.writeInt4(((Range)abstractPosition).getWideLine());
		io.writeInt4(((Range)abstractPosition).getWideCol());
		io.writeInt4(((Range)abstractPosition).getWideEndLine());
		io.writeInt4(((Range)abstractPosition).getWideEndCol());
		io.writeInt4(((Range)strictfpPosition).getPathKey());
		io.writeInt4(((Range)strictfpPosition).getLine());
		io.writeInt4(((Range)strictfpPosition).getCol());
		io.writeInt4(((Range)strictfpPosition).getEndLine());
		io.writeInt4(((Range)strictfpPosition).getEndCol());
		io.writeInt4(((Range)strictfpPosition).getWideLine());
		io.writeInt4(((Range)strictfpPosition).getWideCol());
		io.writeInt4(((Range)strictfpPosition).getWideEndLine());
		io.writeInt4(((Range)strictfpPosition).getWideEndCol());
		io.writeInt4(((Range)parametersStartPosition).getPathKey());
		io.writeInt4(((Range)parametersStartPosition).getLine());
		io.writeInt4(((Range)parametersStartPosition).getCol());
		io.writeInt4(((Range)parametersStartPosition).getEndLine());
		io.writeInt4(((Range)parametersStartPosition).getEndCol());
		io.writeInt4(((Range)parametersStartPosition).getWideLine());
		io.writeInt4(((Range)parametersStartPosition).getWideCol());
		io.writeInt4(((Range)parametersStartPosition).getWideEndLine());
		io.writeInt4(((Range)parametersStartPosition).getWideEndCol());
		io.writeInt4(((Range)parametersEndPosition).getPathKey());
		io.writeInt4(((Range)parametersEndPosition).getLine());
		io.writeInt4(((Range)parametersEndPosition).getCol());
		io.writeInt4(((Range)parametersEndPosition).getEndLine());
		io.writeInt4(((Range)parametersEndPosition).getEndCol());
		io.writeInt4(((Range)parametersEndPosition).getWideLine());
		io.writeInt4(((Range)parametersEndPosition).getWideCol());
		io.writeInt4(((Range)parametersEndPosition).getWideEndLine());
		io.writeInt4(((Range)parametersEndPosition).getWideEndCol());


		io.writeInt4(!factory.getIsFiltered(_hasReturnType) ? _hasReturnType : 0);

		io.writeInt4(!factory.getIsFiltered(_methodType) ? _methodType : 0);

		if (_overrides != null) {
			EdgeIterator<MethodDeclaration> it = getOverridesIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);

		io.writeInt4(((Range)defaultPosition).getPathKey());
		io.writeInt4(((Range)defaultPosition).getLine());
		io.writeInt4(((Range)defaultPosition).getCol());
		io.writeInt4(((Range)defaultPosition).getEndLine());
		io.writeInt4(((Range)defaultPosition).getEndCol());
		io.writeInt4(((Range)defaultPosition).getWideLine());
		io.writeInt4(((Range)defaultPosition).getWideCol());
		io.writeInt4(((Range)defaultPosition).getWideEndLine());
		io.writeInt4(((Range)defaultPosition).getWideEndCol());


		io.writeInt4(!factory.getIsFiltered(_hasDefaultValue) ? _hasDefaultValue : 0);
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
		{
			byte boolValues = io.readByte1();
			isStrictfp = (boolValues & 1) != 0;
			boolValues >>>= 1;
			isAbstract = (boolValues & 1) != 0;
			boolValues >>>= 1;
		}

		((Range)abstractPosition).setPathKey(io.readInt4());
		((Range)abstractPosition).setLine(io.readInt4());
		((Range)abstractPosition).setCol(io.readInt4());
		((Range)abstractPosition).setEndLine(io.readInt4());
		((Range)abstractPosition).setEndCol(io.readInt4());
		((Range)abstractPosition).setWideLine(io.readInt4());
		((Range)abstractPosition).setWideCol(io.readInt4());
		((Range)abstractPosition).setWideEndLine(io.readInt4());
		((Range)abstractPosition).setWideEndCol(io.readInt4());
		((Range)strictfpPosition).setPathKey(io.readInt4());
		((Range)strictfpPosition).setLine(io.readInt4());
		((Range)strictfpPosition).setCol(io.readInt4());
		((Range)strictfpPosition).setEndLine(io.readInt4());
		((Range)strictfpPosition).setEndCol(io.readInt4());
		((Range)strictfpPosition).setWideLine(io.readInt4());
		((Range)strictfpPosition).setWideCol(io.readInt4());
		((Range)strictfpPosition).setWideEndLine(io.readInt4());
		((Range)strictfpPosition).setWideEndCol(io.readInt4());
		((Range)parametersStartPosition).setPathKey(io.readInt4());
		((Range)parametersStartPosition).setLine(io.readInt4());
		((Range)parametersStartPosition).setCol(io.readInt4());
		((Range)parametersStartPosition).setEndLine(io.readInt4());
		((Range)parametersStartPosition).setEndCol(io.readInt4());
		((Range)parametersStartPosition).setWideLine(io.readInt4());
		((Range)parametersStartPosition).setWideCol(io.readInt4());
		((Range)parametersStartPosition).setWideEndLine(io.readInt4());
		((Range)parametersStartPosition).setWideEndCol(io.readInt4());
		((Range)parametersEndPosition).setPathKey(io.readInt4());
		((Range)parametersEndPosition).setLine(io.readInt4());
		((Range)parametersEndPosition).setCol(io.readInt4());
		((Range)parametersEndPosition).setEndLine(io.readInt4());
		((Range)parametersEndPosition).setEndCol(io.readInt4());
		((Range)parametersEndPosition).setWideLine(io.readInt4());
		((Range)parametersEndPosition).setWideCol(io.readInt4());
		((Range)parametersEndPosition).setWideEndLine(io.readInt4());
		((Range)parametersEndPosition).setWideEndCol(io.readInt4());

		_hasReturnType = io.readInt4();
		if (_hasReturnType != 0)
			setParentEdge(_hasReturnType);

		_methodType = io.readInt4();


		_id = io.readInt4();
		if (_id != 0) {
			_overrides = new EdgeList<MethodDeclaration>(factory);
			while (_id != 0) {
				_overrides.add(_id);
				_id = io.readInt4();
			}
		}

		((Range)defaultPosition).setPathKey(io.readInt4());
		((Range)defaultPosition).setLine(io.readInt4());
		((Range)defaultPosition).setCol(io.readInt4());
		((Range)defaultPosition).setEndLine(io.readInt4());
		((Range)defaultPosition).setEndCol(io.readInt4());
		((Range)defaultPosition).setWideLine(io.readInt4());
		((Range)defaultPosition).setWideCol(io.readInt4());
		((Range)defaultPosition).setWideEndLine(io.readInt4());
		((Range)defaultPosition).setWideEndCol(io.readInt4());

		_hasDefaultValue = io.readInt4();
		if (_hasDefaultValue != 0)
			setParentEdge(_hasDefaultValue);
	}

}
