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
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.type.UnboundedWildcardType UnboundedWildcardType} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class UnboundedWildcardTypeImpl extends BaseImpl implements UnboundedWildcardType {

	@SuppressWarnings("unused")
	private static final LoggerHandler logger = new LoggerHandler(UnboundedWildcardTypeImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected int _bound;

	public UnboundedWildcardTypeImpl(int id, Factory factory) {
		super(id, factory);
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkUnboundedWildcardType;
	}

	@Override
	public Type getBound() {
		if (_bound == 0)
			return null;
		if (factory.getIsFiltered(_bound))
			return null;
		return (Type)factory.getRef(_bound);
	}

	@Override
	public void setBound(int _id) {
		if (_bound != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","bound" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkType)) {
			_bound = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setBound(Type _node) {
		if (_bound != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","bound" ));

		_bound = _node.getId();
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



		io.writeInt4(!factory.getIsFiltered(_bound) ? _bound : 0);
	}


	// ---------- Load ----------

	@Override
	public void load(IO io) {


		_bound = io.readInt4();
	}

}
