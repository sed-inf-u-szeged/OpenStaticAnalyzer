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

package columbus;

import java.util.Arrays;

/**
 * Flexible byte array implementation.
 */
public class ByteArray implements Comparable<ByteArray> {
	private int size;
	private byte[] array;

	public ByteArray(int initialCapacity) {
		array = new byte[initialCapacity];
	}

	public ByteArray() {
		this(8);
	}

	public void append(boolean n) {
		ensureCapacity(1);
		array[size++] = n ? (byte)1 : 0;
	}

	public void append(byte n) {
		ensureCapacity(1);
		array[size++] = n;
	}

	public void append(short n) {
		ensureCapacity(2);
		array[size++] = (byte)((n >>> 0) & 0xFF);
		array[size++] = (byte)((n >>> 8) & 0xFF);
	}

	public void append(char n) {
		ensureCapacity(2);
		array[size++] = (byte)((n >>> 0) & 0xFF);
		array[size++] = (byte)((n >>> 8) & 0xFF);
	}

	public void append(int n) {
		ensureCapacity(4);
		array[size++] = (byte)((n >>> 0) & 0xFF);
		array[size++] = (byte)((n >>> 8) & 0xFF);
		array[size++] = (byte)((n >>> 16) & 0xFF);
		array[size++] = (byte)((n >>> 24) & 0xFF);
	}

	public void append(long n) {
		ensureCapacity(8);
		array[size++] = (byte)((n >>> 0) & 0xFF);
		array[size++] = (byte)((n >>> 8) & 0xFF);
		array[size++] = (byte)((n >>> 16) & 0xFF);
		array[size++] = (byte)((n >>> 24) & 0xFF);
		array[size++] = (byte)((n >>> 32) & 0xFF);
		array[size++] = (byte)((n >>> 40) & 0xFF);
		array[size++] = (byte)((n >>> 48) & 0xFF);
		array[size++] = (byte)((n >>> 56) & 0xFF);
	}

	public void append(float n) {
		append(Float.floatToIntBits(n));
	}

	public void append(double n) {
		append(Double.doubleToLongBits(n));
	}

	private void ensureCapacity(int increment) {
		int oldCapacity = array.length;
		int minCapacity = size + increment;
		if (oldCapacity < minCapacity) {
			int newCapacity = (oldCapacity * 3) / 2 + 1;
			if (newCapacity < minCapacity)
				newCapacity = minCapacity;
			array = Arrays.copyOf(array, newCapacity);
		}
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + size;
		for (int i = 0; i < size; ++i) {
			result = prime * result + array[i];
		}
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		ByteArray other = (ByteArray) obj;
		if (size != other.size)
			return false;
		for (int i = 0; i < size; ++i) {
			if (array[i] != other.array[i])
				return false;
		}
		return true;
	}

	@Override
	public int compareTo(ByteArray other) {
		int minSize = size < other.size ? size : other.size;
		for (int i = 0; i < minSize; ++i) {
			if (array[i] < other.array[i])
				return -1;
			if (array[i] > other.array[i])
				return 1;
		}
		if (size < other.size)
			return -1;
		if (size > other.size)
			return 1;
		return 0;
	}

	@Override
	public String toString() {
		return "ByteArray [size=" + size + ", capacity=" + array.length + ", array=" + Arrays.toString(array) + "]";
	}

}
