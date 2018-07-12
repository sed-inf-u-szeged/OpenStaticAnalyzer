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

package columbus;

import java.io.FilterInputStream;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.charset.Charset;
import java.util.zip.InflaterInputStream;
import columbus.logger.LoggerHandler;

/**
 * IO class is responsible for reading/writing fix size data from/to files.
 */
public class IO {

	private static final LoggerHandler logger = new LoggerHandler(StrTable.class,"ColumbusMessages");
	private static final Charset UTF8_CHARSET = Charset.forName("UTF-8");

	public enum IOMode {
		READ, WRITE
	}

	private FilterInputStream in;

	private BufferedOutputStream out;

	public IO(String name, IOMode mode) {
		try {
			if (mode == IOMode.READ) {
				in = new BufferedInputStream(new FileInputStream(name));
			} else if (mode == IOMode.WRITE) {
				out = new BufferedOutputStream(new FileOutputStream(name));
			} else {
				throw new ColumbusException(logger.formatMessage("ext.java.Io.Invalid_IO_mode"));
			}
		} catch (FileNotFoundException e) {
			throw new ColumbusException(e);
		}
	}

	public void close() {
		try {
			if (in != null)
				in.close();
			else if (out != null)
				out.close();
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public void writeUByte1(int n) {
		try {
			out.write((n >>> 0) & 0xFF);
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public void writeUShort2(int n) {
		try {
			out.write((n >>> 0) & 0xFF);
			out.write((n >>> 8) & 0xFF);
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public void writeBoolean1(boolean n) {
		try {
			out.write(n ? 1 : 0);
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public void writeByte1(byte n) {
		try {
			out.write((n >>> 0) & 0xFF);
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public void writeShort2(short n) {
		try {
			out.write((n >>> 0) & 0xFF);
			out.write((n >>> 8) & 0xFF);
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public void writeChar2(char n) {
		try {
			out.write((n >>> 0) & 0xFF);
			out.write((n >>> 8) & 0xFF);
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public void writeInt4(int n) {
		try {
			out.write((n >>> 0) & 0xFF);
			out.write((n >>> 8) & 0xFF);
			out.write((n >>> 16) & 0xFF);
			out.write((n >>> 24) & 0xFF);
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public void writeLong8(long n) {
		try {
			out.write((byte)((n >>> 0) & 0xFF));
			out.write((byte)((n >>> 8) & 0xFF));
			out.write((byte)((n >>> 16) & 0xFF));
			out.write((byte)((n >>> 24) & 0xFF));
			out.write((byte)((n >>> 32) & 0xFF));
			out.write((byte)((n >>> 40) & 0xFF));
			out.write((byte)((n >>> 48) & 0xFF));
			out.write((byte)((n >>> 56) & 0xFF));
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public void writeFloat4(float n) {
		writeInt4(Float.floatToIntBits(n));
	}

	public void writeDouble8(double n) {
		writeLong8(Double.doubleToLongBits(n));
	}

	public void writeShortString(String s) {
		try {
			byte[] bytes = s.getBytes(UTF8_CHARSET);
			int size = bytes.length;
			if (size > 0xFFFF)
				throw new ColumbusException(logger.formatMessage("ext.java.Io.The_string_length"));
			writeUShort2(size);
			out.write(bytes, 0, size);
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public void writeLongString(String s) {
		try {
			byte[] bytes = s.getBytes(UTF8_CHARSET);
			writeInt4(bytes.length);
			out.write(bytes, 0, bytes.length);
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public void writeString(String s) {
		try {
			byte[] bytes = s.getBytes(UTF8_CHARSET);
			out.write(bytes, 0, bytes.length);
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public short readUByte1() {
		try {
			long n = in.read();
			return (short)n;
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public int readUShort2() {
		try {
			long n = in.read();
			n |= in.read() << 8;
			return (int)n;
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public long readUInt4() {
		try {
			long n = in.read();
			n |= in.read() << 8;
			n |= in.read() << 16;
			n |= (long)in.read() << 24;
			return (long)n;
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public boolean readBoolean1() {
		try {
			int n = in.read();
			return n != 0;
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public byte readByte1() {
		try {
			int n = in.read();
			return (byte)n;
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public short readShort2() {
		try {
			int n = in.read();
			n |= in.read() << 8;
			return (short)n;
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public char readChar2() {
		try {
			int n = in.read();
			n |= in.read() << 8;
			return (char)n;
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public int readInt4() {
		try {
			int n = in.read();
			n |= in.read() << 8;
			n |= in.read() << 16;
			n |= in.read() << 24;
			return n;
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public long readLong8() {
		try {
			long n = in.read();
			n |= in.read() << 8;
			n |= in.read() << 16;
			n |= (long)in.read() << 24;
			n |= (long)in.read() << 32;
			n |= (long)in.read() << 40;
			n |= (long)in.read() << 48;
			n |= (long)in.read() << 56;
			return n;
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public float readFloat4() {
		return Float.intBitsToFloat(readInt4());
	}

	public double readDouble8() {
		return Double.longBitsToDouble(readLong8());
	}

	public String readShortString() {
		return readString(readUShort2());
	}

	public String readLongString() {
		return readString(readInt4());
	}

	public String readString(int size) {
		try {
			byte[] array = new byte[size];
			int offset = 0;
			int read = in.read(array, offset, size);
			while (read != size) {
				size -= read;
				offset += read;
				read = in.read(array, offset, size);
				if (read == -1)
					throw new ColumbusException(logger.formatMessage("ext.java.Io.EOF_reached_while_reading"));
			}
			return new String(array, UTF8_CHARSET);
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}

	public void skip(long bytes) {
		try {
			long skipped = in.skip(bytes);
			while (skipped != bytes) {
				bytes -= skipped;
				skipped = in.skip(bytes);
			}
		} catch (IOException e) {
			throw new ColumbusException(e);
		}
	}
	public void setZipedReadMode() {
		if (in != null)
			in = new InflaterInputStream(in);
	}
}
