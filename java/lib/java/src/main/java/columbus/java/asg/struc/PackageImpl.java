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
import columbus.java.asg.base.Comment;
import columbus.java.asg.expr.Annotation;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.struc.Package Package} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class PackageImpl extends BaseImpl implements Package {

	private static final LoggerHandler logger = new LoggerHandler(PackageImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected EdgeList<Comment> _comments;

	protected EdgeList<Annotation> _hasAnnotations;

	protected int name;

	protected Object namePosition;

	protected EdgeList<Member> _hasMembers;

	protected int qualifiedName;

	protected EdgeList<CompilationUnit> _hasCompilationUnits;

	public PackageImpl(int id, Factory factory) {
		super(id, factory);
		namePosition = new Range(factory.getStringTable());
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkPackage;
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
	public String getQualifiedName() {
		return factory.getStringTable().get(qualifiedName);
	}

	@Override
	public int getQualifiedNameKey() {
		return qualifiedName;
	}

	@Override
	public void setQualifiedName(String _qualifiedName) {
		qualifiedName = factory.getStringTable().set(_qualifiedName);
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
	public EdgeIterator<CompilationUnit> getCompilationUnitsIterator() {
		if (_hasCompilationUnits == null)
			return EdgeList.<CompilationUnit>emptyList().iterator();
		else
			return _hasCompilationUnits.iterator();
	}

	@Override
	public boolean getCompilationUnitsIsEmpty() {
		if (_hasCompilationUnits == null)
			return true;
		else
			return _hasCompilationUnits.isEmpty();
	}

	@Override
	public int getCompilationUnitsSize() {
		if (_hasCompilationUnits == null)
			return 0;
		else
			return _hasCompilationUnits.size();
	}

	@Override
	public void addCompilationUnits(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkCompilationUnit) {
			if (_hasCompilationUnits == null)
				_hasCompilationUnits = new EdgeList<CompilationUnit>(factory);
			_hasCompilationUnits.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addCompilationUnits(CompilationUnit _node) {
		if (_hasCompilationUnits == null)
			_hasCompilationUnits = new EdgeList<CompilationUnit>(factory);
		_hasCompilationUnits.add(_node);
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

		if (_hasMembers != null) {
			EdgeIterator<Member> it = getMembersIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);

		io.writeInt4(qualifiedName);

		if (_hasCompilationUnits != null) {
			EdgeIterator<CompilationUnit> it = getCompilationUnitsIterator();
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


		_id = io.readInt4();
		if (_id != 0) {
			_hasMembers = new EdgeList<Member>(factory);
			while (_id != 0) {
				_hasMembers.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}

		qualifiedName = io.readInt4();


		_id = io.readInt4();
		if (_id != 0) {
			_hasCompilationUnits = new EdgeList<CompilationUnit>(factory);
			while (_id != 0) {
				_hasCompilationUnits.add(_id);
				setParentEdge(_id);
				_id = io.readInt4();
			}
		}
	}

}
