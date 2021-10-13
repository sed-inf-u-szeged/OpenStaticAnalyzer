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
import columbus.java.asg.struc.TypeParameter;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.type.TypeVariable TypeVariable} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class TypeVariableImpl extends BaseImpl implements TypeVariable {

	@SuppressWarnings("unused")
	private static final LoggerHandler logger = new LoggerHandler(TypeVariableImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected int _refersTo;

	public TypeVariableImpl(int id, Factory factory) {
		super(id, factory);
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkTypeVariable;
	}

	@Override
	public TypeParameter getRefersTo() {
		if (_refersTo == 0)
			return null;
		if (factory.getIsFiltered(_refersTo))
			return null;
		return (TypeParameter)factory.getRef(_refersTo);
	}

	@Override
	public void setRefersTo(int _id) {
		if (_refersTo != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","refersTo" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (_node.getNodeKind() == NodeKind.ndkTypeParameter) {
			_refersTo = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setRefersTo(TypeParameter _node) {
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



		io.writeInt4(!factory.getIsFiltered(_refersTo) ? _refersTo : 0);
	}


	// ---------- Load ----------

	@Override
	public void load(IO io) {


		_refersTo = io.readInt4();
	}

}
