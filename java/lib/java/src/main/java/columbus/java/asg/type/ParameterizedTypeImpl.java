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

package columbus.java.asg.type;

import columbus.IO;
import columbus.java.asg.*;
import columbus.java.asg.base.BaseImpl;
import columbus.java.asg.base.Base;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.type.ParameterizedType ParameterizedType} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class ParameterizedTypeImpl extends BaseImpl implements ParameterizedType {

	private static final LoggerHandler logger = new LoggerHandler(ParameterizedTypeImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected int _owner;

	protected int _rawType;

	protected EdgeList<Type> _argumentTypes;

	public ParameterizedTypeImpl(int id, Factory factory) {
		super(id, factory);
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkParameterizedType;
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
	public Type getRawType() {
		if (_rawType == 0)
			return null;
		if (factory.getIsFiltered(_rawType))
			return null;
		return (Type)factory.getRef(_rawType);
	}

	@Override
	public EdgeIterator<Type> getArgumentTypesIterator() {
		if (_argumentTypes == null)
			return EdgeList.<Type>emptyList().iterator();
		else
			return _argumentTypes.iterator();
	}

	@Override
	public boolean getArgumentTypesIsEmpty() {
		if (_argumentTypes == null)
			return true;
		else
			return _argumentTypes.isEmpty();
	}

	@Override
	public int getArgumentTypesSize() {
		if (_argumentTypes == null)
			return 0;
		else
			return _argumentTypes.size();
	}

	@Override
	public void setRawType(int _id) {
		if (_rawType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","rawType" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkType)) {
			_rawType = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setRawType(Type _node) {
		if (_rawType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","rawType" ));

		_rawType = _node.getId();
	}

	@Override
	public void addArgumentTypes(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkType)) {
			if (_argumentTypes == null)
				_argumentTypes = new EdgeList<Type>(factory);
			_argumentTypes.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void addArgumentTypes(Type _node) {
		if (_argumentTypes == null)
			_argumentTypes = new EdgeList<Type>(factory);
		_argumentTypes.add(_node);
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


		io.writeInt4(!factory.getIsFiltered(_rawType) ? _rawType : 0);

		if (_argumentTypes != null) {
			EdgeIterator<Type> it = getArgumentTypesIterator();
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


		_owner = io.readInt4();

		_rawType = io.readInt4();


		_id = io.readInt4();
		if (_id != 0) {
			_argumentTypes = new EdgeList<Type>(factory);
			while (_id != 0) {
				_argumentTypes.add(_id);
				_id = io.readInt4();
			}
		}
	}

}
