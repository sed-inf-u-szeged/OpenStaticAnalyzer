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
import columbus.java.asg.expr.TypeExpression;
import columbus.java.asg.base.Positioned;
import columbus.java.asg.base.Comment;
import columbus.java.asg.expr.Annotation;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.struc.InterfaceGeneric InterfaceGeneric} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class InterfaceGenericImpl extends BaseImpl implements InterfaceGeneric {

	private static final LoggerHandler logger = new LoggerHandler(InterfaceGenericImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
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

	protected EdgeList<Member> _hasMembers;

	protected Object typeNamePosition;

	protected boolean isAbstract;

	protected Object abstractPosition;

	protected boolean isStrictfp;

	protected Object strictfpPosition;

	protected int binaryName;

	protected Object extendsPosition;

	protected Object implementsPosition;

	protected Object bodyStartPosition;

	protected int _isInCompilationUnit;

	protected int _hasSuperClass;

	protected EdgeList<TypeExpression> _hasSuperInterfaces;

	protected EdgeList<Positioned> _hasOthers;

	protected EdgeList<TypeParameter> _hasTypeParameters;

	public InterfaceGenericImpl(int id, Factory factory) {
		super(id, factory);
		position = new Range(factory.getStringTable());
		namePosition = new Range(factory.getStringTable());
		accessibilityPosition = new Range(factory.getStringTable());
		staticPosition = new Range(factory.getStringTable());
		finalPosition = new Range(factory.getStringTable());
		typeNamePosition = new Range(factory.getStringTable());
		abstractPosition = new Range(factory.getStringTable());
		strictfpPosition = new Range(factory.getStringTable());
		extendsPosition = new Range(factory.getStringTable());
		implementsPosition = new Range(factory.getStringTable());
		bodyStartPosition = new Range(factory.getStringTable());
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkInterfaceGeneric;
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
	public Range getTypeNamePosition() {
		return (Range)typeNamePosition;
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
	public String getBinaryName() {
		return factory.getStringTable().get(binaryName);
	}

	@Override
	public int getBinaryNameKey() {
		return binaryName;
	}

	@Override
	public Range getExtendsPosition() {
		return (Range)extendsPosition;
	}

	@Override
	public Range getImplementsPosition() {
		return (Range)implementsPosition;
	}

	@Override
	public Range getBodyStartPosition() {
		return (Range)bodyStartPosition;
	}

	@Override
	public void setTypeNamePosition(Range _typeNamePosition) {
		if (factory.getStringTable() == _typeNamePosition.getStringTable())
			typeNamePosition = _typeNamePosition;
		else
			typeNamePosition = new Range(factory.getStringTable(), _typeNamePosition);
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
	public void setBinaryName(String _binaryName) {
		binaryName = factory.getStringTable().set(_binaryName);
	}

	@Override
	public void setExtendsPosition(Range _extendsPosition) {
		if (factory.getStringTable() == _extendsPosition.getStringTable())
			extendsPosition = _extendsPosition;
		else
			extendsPosition = new Range(factory.getStringTable(), _extendsPosition);
	}

	@Override
	public void setImplementsPosition(Range _implementsPosition) {
		if (factory.getStringTable() == _implementsPosition.getStringTable())
			implementsPosition = _implementsPosition;
		else
			implementsPosition = new Range(factory.getStringTable(), _implementsPosition);
	}

	@Override
	public void setBodyStartPosition(Range _bodyStartPosition) {
		if (factory.getStringTable() == _bodyStartPosition.getStringTable())
			bodyStartPosition = _bodyStartPosition;
		else
			bodyStartPosition = new Range(factory.getStringTable(), _bodyStartPosition);
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
	public EdgeIterator<Member> getMembersIterator() {
		if (_hasMembers == null)
			return EdgeList.<Member>emptyList().iterator();
		else
			return _hasMembers.iterator();
	}

	@Override
	public boolean getMembersIsEmpty() {
		if (_hasMembers == null)
			return true;
		else
			return _hasMembers.isEmpty();
	}

	@Override
	public int getMembersSize() {
		if (_hasMembers == null)
			return 0;
		else
			return _hasMembers.size();
	}

	@Override
	public void addMembers(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkMember)) {
			if (_hasMembers == null)
				_hasMembers = new EdgeList<Member>(factory);
			_hasMembers.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addMembers(Member _node) {
		if (_hasMembers == null)
			_hasMembers = new EdgeList<Member>(factory);
		_hasMembers.add(_node);
		setParentEdge(_node);
	}

	@Override
	public CompilationUnit getIsInCompilationUnit() {
		if (_isInCompilationUnit == 0)
			return null;
		if (factory.getIsFiltered(_isInCompilationUnit))
			return null;
		return (CompilationUnit)factory.getRef(_isInCompilationUnit);
	}

	@Override
	public TypeExpression getSuperClass() {
		if (_hasSuperClass == 0)
			return null;
		if (factory.getIsFiltered(_hasSuperClass))
			return null;
		return (TypeExpression)factory.getRef(_hasSuperClass);
	}

	@Override
	public EdgeIterator<TypeExpression> getSuperInterfacesIterator() {
		if (_hasSuperInterfaces == null)
			return EdgeList.<TypeExpression>emptyList().iterator();
		else
			return _hasSuperInterfaces.iterator();
	}

	@Override
	public boolean getSuperInterfacesIsEmpty() {
		if (_hasSuperInterfaces == null)
			return true;
		else
			return _hasSuperInterfaces.isEmpty();
	}

	@Override
	public int getSuperInterfacesSize() {
		if (_hasSuperInterfaces == null)
			return 0;
		else
			return _hasSuperInterfaces.size();
	}

	@Override
	public EdgeIterator<Positioned> getOthersIterator() {
		if (_hasOthers == null)
			return EdgeList.<Positioned>emptyList().iterator();
		else
			return _hasOthers.iterator();
	}

	@Override
	public boolean getOthersIsEmpty() {
		if (_hasOthers == null)
			return true;
		else
			return _hasOthers.isEmpty();
	}

	@Override
	public int getOthersSize() {
		if (_hasOthers == null)
			return 0;
		else
			return _hasOthers.size();
	}

	@Override
	public void setIsInCompilationUnit(int _id) {
		if (_isInCompilationUnit != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","isInCompilationUnit" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkCompilationUnit) {
			_isInCompilationUnit = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setIsInCompilationUnit(CompilationUnit _node) {
		if (_isInCompilationUnit != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","isInCompilationUnit" ));

		_isInCompilationUnit = _node.getId();
	}

	@Override
	public void setSuperClass(int _id) {
		if (_hasSuperClass != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasSuperClass" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkTypeExpression)) {
			_hasSuperClass = _id;
			setParentEdge(_hasSuperClass);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setSuperClass(TypeExpression _node) {
		if (_hasSuperClass != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasSuperClass" ));

		_hasSuperClass = _node.getId();
		setParentEdge(_hasSuperClass);
	}

	@Override
	public void addSuperInterfaces(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkTypeExpression)) {
			if (_hasSuperInterfaces == null)
				_hasSuperInterfaces = new EdgeList<TypeExpression>(factory);
			_hasSuperInterfaces.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addSuperInterfaces(TypeExpression _node) {
		if (_hasSuperInterfaces == null)
			_hasSuperInterfaces = new EdgeList<TypeExpression>(factory);
		_hasSuperInterfaces.add(_node);
		setParentEdge(_node);
	}

	@Override
	public void addOthers(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkPositioned)) {
			if (_hasOthers == null)
				_hasOthers = new EdgeList<Positioned>(factory);
			_hasOthers.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addOthers(Positioned _node) {
		if (_hasOthers == null)
			_hasOthers = new EdgeList<Positioned>(factory);
		_hasOthers.add(_node);
		setParentEdge(_node);
	}

	@Override
	public EdgeIterator<TypeParameter> getTypeParametersIterator() {
		if (_hasTypeParameters == null)
			return EdgeList.<TypeParameter>emptyList().iterator();
		else
			return _hasTypeParameters.iterator();
	}

	@Override
	public boolean getTypeParametersIsEmpty() {
		if (_hasTypeParameters == null)
			return true;
		else
			return _hasTypeParameters.isEmpty();
	}

	@Override
	public int getTypeParametersSize() {
		if (_hasTypeParameters == null)
			return 0;
		else
			return _hasTypeParameters.size();
	}

	@Override
	public void addTypeParameters(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkTypeParameter) {
			if (_hasTypeParameters == null)
				_hasTypeParameters = new EdgeList<TypeParameter>(factory);
			_hasTypeParameters.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addTypeParameters(TypeParameter _node) {
		if (_hasTypeParameters == null)
			_hasTypeParameters = new EdgeList<TypeParameter>(factory);
		_hasTypeParameters.add(_node);
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

		if (_hasMembers != null) {
			EdgeIterator<Member> it = getMembersIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);
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
		io.writeInt4(((Range)typeNamePosition).getPathKey());
		io.writeInt4(((Range)typeNamePosition).getLine());
		io.writeInt4(((Range)typeNamePosition).getCol());
		io.writeInt4(((Range)typeNamePosition).getEndLine());
		io.writeInt4(((Range)typeNamePosition).getEndCol());
		io.writeInt4(((Range)typeNamePosition).getWideLine());
		io.writeInt4(((Range)typeNamePosition).getWideCol());
		io.writeInt4(((Range)typeNamePosition).getWideEndLine());
		io.writeInt4(((Range)typeNamePosition).getWideEndCol());
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
		io.writeInt4(binaryName);
		io.writeInt4(((Range)extendsPosition).getPathKey());
		io.writeInt4(((Range)extendsPosition).getLine());
		io.writeInt4(((Range)extendsPosition).getCol());
		io.writeInt4(((Range)extendsPosition).getEndLine());
		io.writeInt4(((Range)extendsPosition).getEndCol());
		io.writeInt4(((Range)extendsPosition).getWideLine());
		io.writeInt4(((Range)extendsPosition).getWideCol());
		io.writeInt4(((Range)extendsPosition).getWideEndLine());
		io.writeInt4(((Range)extendsPosition).getWideEndCol());
		io.writeInt4(((Range)implementsPosition).getPathKey());
		io.writeInt4(((Range)implementsPosition).getLine());
		io.writeInt4(((Range)implementsPosition).getCol());
		io.writeInt4(((Range)implementsPosition).getEndLine());
		io.writeInt4(((Range)implementsPosition).getEndCol());
		io.writeInt4(((Range)implementsPosition).getWideLine());
		io.writeInt4(((Range)implementsPosition).getWideCol());
		io.writeInt4(((Range)implementsPosition).getWideEndLine());
		io.writeInt4(((Range)implementsPosition).getWideEndCol());
		io.writeInt4(((Range)bodyStartPosition).getPathKey());
		io.writeInt4(((Range)bodyStartPosition).getLine());
		io.writeInt4(((Range)bodyStartPosition).getCol());
		io.writeInt4(((Range)bodyStartPosition).getEndLine());
		io.writeInt4(((Range)bodyStartPosition).getEndCol());
		io.writeInt4(((Range)bodyStartPosition).getWideLine());
		io.writeInt4(((Range)bodyStartPosition).getWideCol());
		io.writeInt4(((Range)bodyStartPosition).getWideEndLine());
		io.writeInt4(((Range)bodyStartPosition).getWideEndCol());


		io.writeInt4(!factory.getIsFiltered(_isInCompilationUnit) ? _isInCompilationUnit : 0);

		io.writeInt4(!factory.getIsFiltered(_hasSuperClass) ? _hasSuperClass : 0);

		if (_hasSuperInterfaces != null) {
			EdgeIterator<TypeExpression> it = getSuperInterfacesIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);

		if (_hasOthers != null) {
			EdgeIterator<Positioned> it = getOthersIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);

		if (_hasTypeParameters != null) {
			EdgeIterator<TypeParameter> it = getTypeParametersIterator();
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


		_id = io.readInt4();
		if (_id != 0) {
			_hasMembers = new EdgeList<Member>(factory);
			while (_id != 0) {
				_hasMembers.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}
		{
			byte boolValues = io.readByte1();
			isStrictfp = (boolValues & 1) != 0;
			boolValues >>>= 1;
			isAbstract = (boolValues & 1) != 0;
			boolValues >>>= 1;
		}

		((Range)typeNamePosition).setPathKey(io.readInt4());
		((Range)typeNamePosition).setLine(io.readInt4());
		((Range)typeNamePosition).setCol(io.readInt4());
		((Range)typeNamePosition).setEndLine(io.readInt4());
		((Range)typeNamePosition).setEndCol(io.readInt4());
		((Range)typeNamePosition).setWideLine(io.readInt4());
		((Range)typeNamePosition).setWideCol(io.readInt4());
		((Range)typeNamePosition).setWideEndLine(io.readInt4());
		((Range)typeNamePosition).setWideEndCol(io.readInt4());
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
		binaryName = io.readInt4();
		((Range)extendsPosition).setPathKey(io.readInt4());
		((Range)extendsPosition).setLine(io.readInt4());
		((Range)extendsPosition).setCol(io.readInt4());
		((Range)extendsPosition).setEndLine(io.readInt4());
		((Range)extendsPosition).setEndCol(io.readInt4());
		((Range)extendsPosition).setWideLine(io.readInt4());
		((Range)extendsPosition).setWideCol(io.readInt4());
		((Range)extendsPosition).setWideEndLine(io.readInt4());
		((Range)extendsPosition).setWideEndCol(io.readInt4());
		((Range)implementsPosition).setPathKey(io.readInt4());
		((Range)implementsPosition).setLine(io.readInt4());
		((Range)implementsPosition).setCol(io.readInt4());
		((Range)implementsPosition).setEndLine(io.readInt4());
		((Range)implementsPosition).setEndCol(io.readInt4());
		((Range)implementsPosition).setWideLine(io.readInt4());
		((Range)implementsPosition).setWideCol(io.readInt4());
		((Range)implementsPosition).setWideEndLine(io.readInt4());
		((Range)implementsPosition).setWideEndCol(io.readInt4());
		((Range)bodyStartPosition).setPathKey(io.readInt4());
		((Range)bodyStartPosition).setLine(io.readInt4());
		((Range)bodyStartPosition).setCol(io.readInt4());
		((Range)bodyStartPosition).setEndLine(io.readInt4());
		((Range)bodyStartPosition).setEndCol(io.readInt4());
		((Range)bodyStartPosition).setWideLine(io.readInt4());
		((Range)bodyStartPosition).setWideCol(io.readInt4());
		((Range)bodyStartPosition).setWideEndLine(io.readInt4());
		((Range)bodyStartPosition).setWideEndCol(io.readInt4());

		_isInCompilationUnit = io.readInt4();

		_hasSuperClass = io.readInt4();
		if (_hasSuperClass != 0)
			setParentEdge(_hasSuperClass);


		_id = io.readInt4();
		if (_id != 0) {
			_hasSuperInterfaces = new EdgeList<TypeExpression>(factory);
			while (_id != 0) {
				_hasSuperInterfaces.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}

		_id = io.readInt4();
		if (_id != 0) {
			_hasOthers = new EdgeList<Positioned>(factory);
			while (_id != 0) {
				_hasOthers.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}


		_id = io.readInt4();
		if (_id != 0) {
			_hasTypeParameters = new EdgeList<TypeParameter>(factory);
			while (_id != 0) {
				_hasTypeParameters.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}
	}

}
