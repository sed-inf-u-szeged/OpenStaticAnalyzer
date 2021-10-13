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
 * Implementation class for the {@link columbus.java.asg.type.IntersectionType IntersectionType} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class IntersectionTypeImpl extends BaseImpl implements IntersectionType {

	@SuppressWarnings("unused")
	private static final LoggerHandler logger = new LoggerHandler(IntersectionTypeImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected EdgeList<Type> _bounds;

	public IntersectionTypeImpl(int id, Factory factory) {
		super(id, factory);
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkIntersectionType;
	}

	@Override
	public EdgeIterator<Type> getBoundsIterator() {
		if (_bounds == null)
			return EdgeList.<Type>emptyList().iterator();
		else
			return _bounds.iterator();
	}

	@Override
	public boolean getBoundsIsEmpty() {
		if (_bounds == null)
			return true;
		else
			return _bounds.isEmpty();
	}

	@Override
	public int getBoundsSize() {
		if (_bounds == null)
			return 0;
		else
			return _bounds.size();
	}

	@Override
	public void addBounds(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkType)) {
			if (_bounds == null)
				_bounds = new EdgeList<Type>(factory);
			_bounds.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void addBounds(Type _node) {
		if (_bounds == null)
			_bounds = new EdgeList<Type>(factory);
		_bounds.add(_node);
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


		if (_bounds != null) {
			EdgeIterator<Type> it = getBoundsIterator();
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
			_bounds = new EdgeList<Type>(factory);
			while (_id != 0) {
				_bounds.add(_id);
				_id = io.readInt4();
			}
		}
	}

}
