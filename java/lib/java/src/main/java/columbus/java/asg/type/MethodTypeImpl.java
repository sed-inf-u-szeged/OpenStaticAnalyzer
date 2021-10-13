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
 * Implementation class for the {@link columbus.java.asg.type.MethodType MethodType} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class MethodTypeImpl extends BaseImpl implements MethodType {

	@SuppressWarnings("unused")
	private static final LoggerHandler logger = new LoggerHandler(MethodTypeImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected int _returnType;

	protected EdgeList<Type> _parameterTypes;

	protected EdgeList<Type> _thrownTypes;

	public MethodTypeImpl(int id, Factory factory) {
		super(id, factory);
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkMethodType;
	}

	@Override
	public Type getReturnType() {
		if (_returnType == 0)
			return null;
		if (factory.getIsFiltered(_returnType))
			return null;
		return (Type)factory.getRef(_returnType);
	}

	@Override
	public EdgeIterator<Type> getParameterTypesIterator() {
		if (_parameterTypes == null)
			return EdgeList.<Type>emptyList().iterator();
		else
			return _parameterTypes.iterator();
	}

	@Override
	public boolean getParameterTypesIsEmpty() {
		if (_parameterTypes == null)
			return true;
		else
			return _parameterTypes.isEmpty();
	}

	@Override
	public int getParameterTypesSize() {
		if (_parameterTypes == null)
			return 0;
		else
			return _parameterTypes.size();
	}

	@Override
	public EdgeIterator<Type> getThrownTypesIterator() {
		if (_thrownTypes == null)
			return EdgeList.<Type>emptyList().iterator();
		else
			return _thrownTypes.iterator();
	}

	@Override
	public boolean getThrownTypesIsEmpty() {
		if (_thrownTypes == null)
			return true;
		else
			return _thrownTypes.isEmpty();
	}

	@Override
	public int getThrownTypesSize() {
		if (_thrownTypes == null)
			return 0;
		else
			return _thrownTypes.size();
	}

	@Override
	public void setReturnType(int _id) {
		if (_returnType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","returnType" ));

		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkType)) {
			_returnType = _id;
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void setReturnType(Type _node) {
		if (_returnType != 0)
			throw new JavaException(logger.formatMessage("ex.java.Node.The_previous_end_point","returnType" ));

		_returnType = _node.getId();
	}

	@Override
	public void addParameterTypes(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkType)) {
			if (_parameterTypes == null)
				_parameterTypes = new EdgeList<Type>(factory);
			_parameterTypes.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void addParameterTypes(Type _node) {
		if (_parameterTypes == null)
			_parameterTypes = new EdgeList<Type>(factory);
		_parameterTypes.add(_node);
	}

	@Override
	public void addThrownTypes(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkType)) {
			if (_thrownTypes == null)
				_thrownTypes = new EdgeList<Type>(factory);
			_thrownTypes.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void addThrownTypes(Type _node) {
		if (_thrownTypes == null)
			_thrownTypes = new EdgeList<Type>(factory);
		_thrownTypes.add(_node);
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



		io.writeInt4(!factory.getIsFiltered(_returnType) ? _returnType : 0);

		if (_parameterTypes != null) {
			EdgeIterator<Type> it = getParameterTypesIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);

		if (_thrownTypes != null) {
			EdgeIterator<Type> it = getThrownTypesIterator();
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


		_returnType = io.readInt4();


		_id = io.readInt4();
		if (_id != 0) {
			_parameterTypes = new EdgeList<Type>(factory);
			while (_id != 0) {
				_parameterTypes.add(_id);
				_id = io.readInt4();
			}
		}

		_id = io.readInt4();
		if (_id != 0) {
			_thrownTypes = new EdgeList<Type>(factory);
			while (_id != 0) {
				_thrownTypes.add(_id);
				_id = io.readInt4();
			}
		}
	}

}
