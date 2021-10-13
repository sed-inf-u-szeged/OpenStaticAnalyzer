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
import columbus.java.asg.base.Positioned;
import columbus.java.asg.base.Comment;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.struc.CompilationUnit CompilationUnit} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class CompilationUnitImpl extends BaseImpl implements CompilationUnit {

	@SuppressWarnings("unused")
	private static final LoggerHandler logger = new LoggerHandler(CompilationUnitImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected Object position;

	protected EdgeList<Comment> _comments;

	protected int fileEncoding;

	protected int _hasPackageDeclaration;

	protected EdgeList<Import> _hasImports;

	protected EdgeList<Positioned> _hasOthers;

	protected int _hasModuleDeclaration;

	protected EdgeList<TypeDeclaration> _typeDeclarations;

	protected int _isInModule;

	public CompilationUnitImpl(int id, Factory factory) {
		super(id, factory);
		position = new Range(factory.getStringTable());
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkCompilationUnit;
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
	public String getFileEncoding() {
		return factory.getStringTable().get(fileEncoding);
	}

	@Override
	public int getFileEncodingKey() {
		return fileEncoding;
	}

	@Override
	public void setFileEncoding(String _fileEncoding) {
		fileEncoding = factory.getStringTable().set(_fileEncoding);
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
	public PackageDeclaration getPackageDeclaration() {
		if (_hasPackageDeclaration == 0)
			return null;
		if (factory.getIsFiltered(_hasPackageDeclaration))
			return null;
		return (PackageDeclaration)factory.getRef(_hasPackageDeclaration);
	}

	@Override
	public EdgeIterator<Import> getImportsIterator() {
		if (_hasImports == null)
			return EdgeList.<Import>emptyList().iterator();
		else
			return _hasImports.iterator();
	}

	@Override
	public boolean getImportsIsEmpty() {
		if (_hasImports == null)
			return true;
		else
			return _hasImports.isEmpty();
	}

	@Override
	public int getImportsSize() {
		if (_hasImports == null)
			return 0;
		else
			return _hasImports.size();
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
	public ModuleDeclaration getModuleDeclaration() {
		if (_hasModuleDeclaration == 0)
			return null;
		if (factory.getIsFiltered(_hasModuleDeclaration))
			return null;
		return (ModuleDeclaration)factory.getRef(_hasModuleDeclaration);
	}

	@Override
	public EdgeIterator<TypeDeclaration> getTypeDeclarationsIterator() {
		if (_typeDeclarations == null)
			return EdgeList.<TypeDeclaration>emptyList().iterator();
		else
			return _typeDeclarations.iterator();
	}

	@Override
	public boolean getTypeDeclarationsIsEmpty() {
		if (_typeDeclarations == null)
			return true;
		else
			return _typeDeclarations.isEmpty();
	}

	@Override
	public int getTypeDeclarationsSize() {
		if (_typeDeclarations == null)
			return 0;
		else
			return _typeDeclarations.size();
	}

	@Override
	public Module getIsInModule() {
		if (_isInModule == 0)
			return null;
		if (factory.getIsFiltered(_isInModule))
			return null;
		return (Module)factory.getRef(_isInModule);
	}

	@Override
	public void setPackageDeclaration(int _id) {
		if (_hasPackageDeclaration != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasPackageDeclaration" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkPackageDeclaration) {
			_hasPackageDeclaration = _id;
			setParentEdge(_hasPackageDeclaration);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setPackageDeclaration(PackageDeclaration _node) {
		if (_hasPackageDeclaration != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasPackageDeclaration" ));

		_hasPackageDeclaration = _node.getId();
		setParentEdge(_hasPackageDeclaration);
	}

	@Override
	public void addImports(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkImport) {
			if (_hasImports == null)
				_hasImports = new EdgeList<Import>(factory);
			_hasImports.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
		setParentEdge(_id);
	}

	@Override
	public void addImports(Import _node) {
		if (_hasImports == null)
			_hasImports = new EdgeList<Import>(factory);
		_hasImports.add(_node);
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
	public void setModuleDeclaration(int _id) {
		if (_hasModuleDeclaration != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasModuleDeclaration" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkModuleDeclaration) {
			_hasModuleDeclaration = _id;
			setParentEdge(_hasModuleDeclaration);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setModuleDeclaration(ModuleDeclaration _node) {
		if (_hasModuleDeclaration != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","hasModuleDeclaration" ));

		_hasModuleDeclaration = _node.getId();
		setParentEdge(_hasModuleDeclaration);
	}

	@Override
	public void addTypeDeclarations(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkTypeDeclaration)) {
			if (_typeDeclarations == null)
				_typeDeclarations = new EdgeList<TypeDeclaration>(factory);
			_typeDeclarations.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void addTypeDeclarations(TypeDeclaration _node) {
		if (_typeDeclarations == null)
			_typeDeclarations = new EdgeList<TypeDeclaration>(factory);
		_typeDeclarations.add(_node);
	}

	@Override
	public void setIsInModule(int _id) {
		if (_isInModule != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","isInModule" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkModule) {
			_isInModule = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setIsInModule(Module _node) {
		if (_isInModule != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","isInModule" ));

		_isInModule = _node.getId();
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


		io.writeInt4(((Range)position).getPathKey());
		io.writeInt4(((Range)position).getLine());
		io.writeInt4(((Range)position).getCol());
		io.writeInt4(((Range)position).getEndLine());
		io.writeInt4(((Range)position).getEndCol());
		io.writeInt4(((Range)position).getWideLine());
		io.writeInt4(((Range)position).getWideCol());
		io.writeInt4(((Range)position).getWideEndLine());
		io.writeInt4(((Range)position).getWideEndCol());

		if (_comments != null) {
			EdgeIterator<Comment> it = getCommentsIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);

		io.writeInt4(fileEncoding);


		io.writeInt4(!factory.getIsFiltered(_hasPackageDeclaration) ? _hasPackageDeclaration : 0);

		io.writeInt4(!factory.getIsFiltered(_hasModuleDeclaration) ? _hasModuleDeclaration : 0);

		io.writeInt4(!factory.getIsFiltered(_isInModule) ? _isInModule : 0);

		if (_hasImports != null) {
			EdgeIterator<Import> it = getImportsIterator();
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

		if (_typeDeclarations != null) {
			EdgeIterator<TypeDeclaration> it = getTypeDeclarationsIterator();
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


		((Range)position).setPathKey(io.readInt4());
		((Range)position).setLine(io.readInt4());
		((Range)position).setCol(io.readInt4());
		((Range)position).setEndLine(io.readInt4());
		((Range)position).setEndCol(io.readInt4());
		((Range)position).setWideLine(io.readInt4());
		((Range)position).setWideCol(io.readInt4());
		((Range)position).setWideEndLine(io.readInt4());
		((Range)position).setWideEndCol(io.readInt4());


		_id = io.readInt4();
		if (_id != 0) {
			_comments = new EdgeList<Comment>(factory);
			while (_id != 0) {
				_comments.add(_id);
				_id = io.readInt4();
			}
		}

		fileEncoding = io.readInt4();

		_hasPackageDeclaration = io.readInt4();
		if (_hasPackageDeclaration != 0)
			setParentEdge(_hasPackageDeclaration);

		_hasModuleDeclaration = io.readInt4();
		if (_hasModuleDeclaration != 0)
			setParentEdge(_hasModuleDeclaration);

		_isInModule = io.readInt4();


		_id = io.readInt4();
		if (_id != 0) {
			_hasImports = new EdgeList<Import>(factory);
			while (_id != 0) {
				_hasImports.add(_id);
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
			_typeDeclarations = new EdgeList<TypeDeclaration>(factory);
			while (_id != 0) {
				_typeDeclarations.add(_id);
				_id = io.readInt4();
			}
		}
	}

}
