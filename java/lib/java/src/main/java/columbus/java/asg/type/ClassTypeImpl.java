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

package columbus.java.asg.type;

import columbus.IO;
import columbus.java.asg.*;
import columbus.java.asg.base.BaseImpl;
import columbus.java.asg.base.Base;
import columbus.java.asg.struc.TypeDeclaration;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.type.ClassType ClassType} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class ClassTypeImpl extends BaseImpl implements ClassType {

	@SuppressWarnings("unused")
	private static final LoggerHandler logger = new LoggerHandler(ClassTypeImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected int _owner;

	protected int _refersTo;

	public ClassTypeImpl(int id, Factory factory) {
		super(id, factory);
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkClassType;
	}

	@Override
	public Type getOwner() {
		if (_owner == 0)
			return null;
		if (factory.getIsFiltered(_owner))
			return null;
		return (Type)factory.getRef(_owner);
	}

	@Override
	public void setOwner(int _id) {
		if (_owner != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","owner" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkType)) {
			_owner = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setOwner(Type _node) {
		if (_owner != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","owner" ));

		_owner = _node.getId();
	}

	@Override
	public TypeDeclaration getRefersTo() {
		if (_refersTo == 0)
			return null;
		if (factory.getIsFiltered(_refersTo))
			return null;
		return (TypeDeclaration)factory.getRef(_refersTo);
	}

	@Override
	public void setRefersTo(int _id) {
		if (_refersTo != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","refersTo" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkTypeDeclaration)) {
			_refersTo = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setRefersTo(TypeDeclaration _node) {
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



		io.writeInt4(!factory.getIsFiltered(_owner) ? _owner : 0);


		io.writeInt4(!factory.getIsFiltered(_refersTo) ? _refersTo : 0);
	}


	// ---------- Load ----------

	@Override
	public void load(IO io) {


		_owner = io.readInt4();

		_refersTo = io.readInt4();
	}

}
