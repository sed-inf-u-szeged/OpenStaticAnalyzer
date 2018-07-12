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

using System;
using System.Collections.Generic;
using System.IO;

namespace Columbus
{

    public enum HeaderDataTypeKind {
      hdkPropertyData,
      hdkIntervalData,
      hdkAnalysisData,
      hdkLinkerCompilationData,
      hdkLimOrigin,
      hdkOverride
    };
    /// <summary>
    /// IO class is responsible for reading/writing fix size data from file.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else

    public
#endif
    class IO : IDisposable
    {
        /// <summary>The file.</summary>
        protected FileStream fileStream;

        protected long blockSizePosition;

        /// <summary>Dispose information for the Garbage Collector.</summary>
        protected bool isDisposed = false;

        /// <summary>
        /// Creates an IO object and opens a file in a given mode.
        /// </summary>
        /// <param name="fileName">[in] The name of the file.</param>
        /// <param name="mode">[in] The file will be opened in the given mode.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the opening of the file in a given mode failed.</exception>
        public IO(string fileName, FileMode mode)
        {
            try
            {
                fileStream = new FileStream(fileName, mode);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.IO()", "Can not open file: " + fileName, exception);
            }
        }

        /// <summary>
        /// Simple destructor.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Destructor.
        /// </summary>
        protected virtual void Dispose(bool isDisposing)
        {
            if (!isDisposed)
            {
                if (fileStream != null)
                {
                    try
                    {
                        fileStream.Close();
                        fileStream = null;
                    }
                    catch (System.Exception exception)
                    {
                        throw new ColumbusIOException("Columbus.IO.close()", "Closing of the file is failed!", exception);
                    }
                }

                isDisposed = true;
            }
        }

        /// <summary>
        /// Destructor for the Garbage Collector.
        /// </summary>
        ~IO()
        {
            Dispose(false);
        }

        /// <summary>
        /// Closes the opened file.
        /// </summary>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the file is already closed.</exception>
        public void close()
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.close()", "The file is already closed");

            try
            {
                fileStream.Close();
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.close()", "Closing of the file is failed!", exception);
            }

            fileStream = null;
        }


        public void writeStartSizeOfBlock()
        {
            blockSizePosition = fileStream.Position;
            writeULong8(0);
        }

        public void writeEndSizeOfBlock()
        {
            long filePos = fileStream.Position;
            fileStream.Seek(blockSizePosition,SeekOrigin.Begin);
            long i = filePos - blockSizePosition;
            writeULong8((ulong)i);
            fileStream.Seek(0, SeekOrigin.End);
        }

        /// <summary>
        /// Writes an unsigned long on 4 bytes to the file.
        /// </summary>
        /// <param name="obj">[in] The unsigned long value to write.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the writing failed.</exception>
        public void writeULong4(uint obj)
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.writeULong4()", "The file is closed");

            try
            {
                fileStream.Write(BitConverter.GetBytes(obj),0,4);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.writeULong4()", "Writing error", exception);
            }
        }

        /// <summary>
        /// Reads 4 bytes into an unsigned long from the file.
        /// </summary>
        /// <returns>The value read from the file.</returns>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the reading failed.</exception>
        public uint readULong4()
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.readULong4()", "The file is closed");

            try
            {
                byte[] byteBuffer = new byte[4];
                if (fileStream.Read(byteBuffer, 0, 4) != 4)
                    throw new System.Exception();
                return BitConverter.ToUInt32(byteBuffer, 0);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.readULong4()", "Reading error", exception);
            }
        }

        /// <summary>
        /// Writes an unsigned byte on 1 byte to the file.
        /// </summary>
        /// <param name="obj">[in] The unsigned byte value to write.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the writing failed.</exception>
        public void writeUByte1(byte obj)
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.writeUByte1()", "The file is closed");

            try
            {
                fileStream.WriteByte(obj);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.writeUByte1()", "Writing error", exception);
            }
        }

        /// <summary>
        /// Reads 1 byte into a byte from the file.
        /// </summary>
        /// <returns>The value read from the file.</returns>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the reading failed.</exception>
        public byte readUByte1()
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.readUByte1()", "The file is closed");

            try
            {
                byte[] byteBuffer = new byte[1];
                if (fileStream.Read(byteBuffer, 0, 1) != 1)
                    throw new System.Exception();
                return byteBuffer[0];
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.readUByte1()", "Reading error", exception);
            }
        }

        /// <summary>
        /// Writes a bool on 1 byte to the file.
        /// </summary>
        /// <param name="obj">[in] The bool value to write.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the writing failed.</exception>
        public void writeBool1(bool obj)
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.writeBool1()", "The file is closed");

            try
            {
                fileStream.Write(BitConverter.GetBytes(obj), 0, 1);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.writeBool1()", "Writing error", exception);
            }
        }

        /// <summary>
        /// Reads 1 byte into a bool from the file.
        /// </summary>
        /// <returns>The value read from the file.</returns>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the reading failed.</exception>
        public bool readBool1()
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.readBool1()", "The file is closed");

            try
            {
                byte[] byteBuffer = new byte[1];
                if (fileStream.Read(byteBuffer, 0, 1) != 1)
                    throw new System.Exception();
                return BitConverter.ToBoolean(byteBuffer, 0);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.readBool1()", "Reading error", exception);
            }
        }

        /// <summary>
        /// Writes a double on 8 bytes to the file.
        /// </summary>
        /// <param name="obj">[in] The double value to write.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the writing failed.</exception>
        public void writeDouble8(double obj)
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.writeDouble8()", "The file is closed");

            try
            {
                fileStream.Write(BitConverter.GetBytes(obj), 0, 8);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.writeDouble8()", "Writing error", exception);
            }
        }

        /// <summary>
        /// Reads 8 bytes into a double from the file.
        /// </summary>
        /// <returns>The value read from the file.</returns>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the reading failed.</exception>
        public double readDouble8()
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.readDouble8()", "The file is closed");

            try
            {
                byte[] byteBuffer = new byte[8];
                if (fileStream.Read(byteBuffer, 0, 8) != 8)
                    throw new System.Exception();
                return BitConverter.ToDouble(byteBuffer, 0);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.readDouble8()", "Reading error", exception);
            }
        }

        /// <summary>
        /// Writes a short (maximum 65535 length) string and its length to the file.
        /// </summary>
        /// <param name="obj">[in] The string to write.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the writing failed.</exception>
        public void writeShortString(string obj)
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.writeShortString()", "The file is closed");

            if (obj.Length > 0xFFFF)
                throw new ColumbusIOException("Columbus.IO.writeShortString()", "The string length is greater than 65535");

            try
            {
                ushort size = (ushort)obj.Length;
                writeUShort2(size);
                fileStream.Write(System.Text.Encoding.Default.GetBytes(obj), 0, size);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.writeShortString()", "Writing error", exception);
            }
        }

        /// <summary>
        /// Reads a maximum 65535 length string from the file.
        /// </summary>
        /// <returns>The value read from the file.</returns>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the reading failed.</exception>
        public string readShortString()
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.readShortString()", "The file is closed");

            try
            {
                ushort length = readUShort2();

                byte[] byteObj = new byte[length];
                if (fileStream.Read(byteObj, 0, length) != length)
                    throw new System.Exception();

                return System.Text.Encoding.UTF8.GetString(byteObj);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.readShortString()", "Reading error", exception);
            }
        }

        /// <summary>
        /// Writes a string and its length to the file.
        /// </summary>
        /// <param name="obj">[in] The string to write.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the writing failed.</exception>
        public void writeString(string obj)
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.writeString()", "The file is closed");

            try
            {
                if (obj.Length != 0)
                {
                    byte[] byteBufferToWrite = System.Text.Encoding.Default.GetBytes(obj);
                    fileStream.Write(byteBufferToWrite, 0, byteBufferToWrite.Length);
                    writeUByte1(0);
                }
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.writeString()", "Writing error", exception);
            }
        }

        /// <summary>
        /// Reads the length and then the actual string from the file.
        /// </summary>
        /// <returns>The value read from the file.</returns>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the reading failed.</exception>
        public string readString()
        {
            return readString(-1);
        }


        public void writeData(string str, int size)
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.readString()", "The file is closed");

            try
            {
                byte[] byteObj = System.Text.Encoding.Default.GetBytes(str); ;

                fileStream.Write(byteObj, 0, size);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.readString()", "Reading error", exception);
            }
        }

        public void readData(out string str, int size)
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.readString()", "The file is closed");

            try
            {
                byte[] byteObj = new byte[size];
                if (fileStream.Read(byteObj, 0, size) != size)
                    throw new System.Exception();

                str = System.Text.Encoding.Default.GetString(byteObj);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.readString()", "Reading error", exception);
            }
        }

        /// <summary>
        /// Reads a string from the file.
        /// </summary>
        /// <param name="readLength">[in] The length of the string to read. If it's (-1) then the length will be read from the file.</param>
        /// <returns>The value read from the file.</returns>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the reading failed.</exception>
        public string readString(int readLength)
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.readString()", "The file is closed");

            try
            {
                int length = readLength;

                if (length == -1)
                {
                    byte[] byteBuffer = new byte[4];
                    if (fileStream.Read(byteBuffer, 0, 4) != 4)
                        throw new System.Exception();
                    length = readUShort2();
                }

                byte[] byteObj = new byte[length];
                if (fileStream.Read(byteObj, 0, length) != length)
                    throw new System.Exception();

                return System.Text.Encoding.UTF8.GetString(byteObj);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.readString()", "Reading error", exception);
            }
        }

        /// <summary>
        /// Writes an unsigned int on 4 bytes to the file.
        /// </summary>
        /// <param name="obj">[in] The unsigned int value to write.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the writing failed.</exception>
        public void writeUInt4(uint obj)
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.writeUInt4()", "The file is closed");

            try
            {
                fileStream.Write(BitConverter.GetBytes(obj), 0, 4);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.writeUInt4()", "Writing error", exception);
            }
        }

        /// <summary>
        /// Reads 4 bytes into an unsigned int from the file.
        /// </summary>
        /// <returns>The value read from the file.</returns>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the reading failed.</exception>
        public uint readUInt4()
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.readUInt4()", "The file is closed");

            try
            {
                byte[] byteBuffer = new byte[4];
                if (fileStream.Read(byteBuffer, 0, 4) != 4)
                    throw new System.Exception();
                return BitConverter.ToUInt32(byteBuffer, 0);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.readUInt4()", "Reading error", exception);
            }
        }

        /// <summary>
        /// Writes an unsigned long on 8 bytes to the file.
        /// </summary>
        /// <param name="obj">[in] The unsigned long value to write.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the writing failed.</exception>
        public void writeULong8(ulong obj)
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.writeULong8()", "The file is closed");

            try
            {
                fileStream.Write(BitConverter.GetBytes(obj), 0, 8);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.writeULong8()", "Writing error", exception);
            }
        }

        /// <summary>
        /// Reads 8 bytes into an unsigned long from the file.
        /// </summary>
        /// <returns>The value read from the file.</returns>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the reading failed.</exception>
        public ulong readULong8()
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.readULong8()", "The file is closed");

            try
            {
                byte[] byteBuffer = new byte[8];
                if (fileStream.Read(byteBuffer, 0, 8) != 8)
                    throw new System.Exception();
                return BitConverter.ToUInt64(byteBuffer, 0);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.readULong8()", "Reading error", exception);
            }
        }

        /// <summary>
        /// Writes an unsigned short on 4 bytes to the file.
        /// </summary>
        /// <param name="obj">[in] The unsigned short value to write.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the writing failed.</exception>
        public void writeUShort2(ushort obj)
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.writeUShort2()", "The file is closed");

            try
            {
                fileStream.Write(BitConverter.GetBytes(obj), 0, 2);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.writeUShort2()", "Writing error", exception);
            }
        }

        /// <summary>
        /// Reads 2 bytes into an unsigned short from the file.
        /// </summary>
        /// <returns>The value read from the file.</returns>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the reading failed.</exception>
        public ushort readUShort2()
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.readUShort2()", "The file is closed");

            try
            {
                byte[] byteBuffer = new byte[2];
                if (fileStream.Read(byteBuffer, 0, 2) != 2)
                    throw new System.Exception();
                return BitConverter.ToUInt16(byteBuffer, 0);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.readUShort2()", "Reading error", exception);
            }
        }

        /// <summary>
        /// Writes a float on 4 bytes to the file.
        /// </summary>
        /// <param name="obj">[in] The float value to write.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the writing failed.</exception>
        public void writeFloat4(float obj)
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.writeFloat4()", "The file is closed");

            try
            {
                fileStream.Write(BitConverter.GetBytes(obj), 0, 4);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.writeFloat4()", "Writing error", exception);
            }
        }

        /// <summary>
        /// Reads 4 bytes into a float from the file.
        /// </summary>
        /// <returns>The value read from the file.</returns>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if the reading failed.</exception>
        public float readFloat4()
        {
            if (fileStream == null)
                throw new ColumbusIOException("Columbus.IO.readFloat4()", "The file is closed");

            try
            {
                byte[] byteBuffer = new byte[4];
                if (fileStream.Read(byteBuffer, 0, 4) != 4)
                    throw new System.Exception();
                return System.BitConverter.ToSingle(byteBuffer, 0);
            }
            catch (System.Exception exception)
            {
                throw new ColumbusIOException("Columbus.IO.readFloat4()", "Reading error", exception);
            }
        }

        public void vSkip(long _byte)
        {
            try
            {
                fileStream.Seek(_byte, SeekOrigin.Current);
            }
            catch (Exception ex)
            {
                throw new ColumbusIOException("Columbus.IO.vSkip(" + _byte + ")", "Reading error", ex);
            }
        }
    }


#if (LIM_INTERNAL)
    internal
#else

    public
#endif
    interface IHeaderData
    {
        /// <summary>
        /// Saves the header data to the given file.
        /// </summary>
        /// <param name="binIo"></param>
        void save(IO binIo);

        /// <summary>
        /// loading the header data
        /// </summary>
        /// <param name="binIo"></param>
        void load(IO binIo);

        /// <summary>
        /// get headerdata type
        /// </summary>
        /// <returns>the type of the header</returns>
        HeaderDataTypeKind Type { get; }

    }


    /// <summary>
    /// CsiHeader class is responsible for storing/loading/saving the columbus schema instance headers.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else

    public
#endif
    class PropertyData : IHeaderData
    {
        /// <summary>Contains the (key, value) pairs of the header.</summary>
        public Dictionary<string, string> header { get; private set; }

        /// <summary>
        /// Creates a CsiHeader object.
        /// </summary>
        public PropertyData()
        {
            header = new Dictionary<string, string>();
        }

        /// <summary>
        /// Add a new (key, vale) pair to the header.
        /// </summary>
        /// <param name="key">[in] The key.</param>
        /// <param name="value">[in] The string to store beside the key.</param>
        /// <returns>Returns true if the insertion was success. In case an item with same key already exist the function returns false.</returns>
        public bool add(string key, string value)
        {
            if (header.ContainsKey(key))
                return false;

            header.Add(key, value);

            return true;
        }

        public HeaderDataTypeKind Type
        {
            get
            {
                return HeaderDataTypeKind.hdkPropertyData;
            }
        }

        /// <summary>
        /// Add a new (key,vale) pair to the header. If the value is true than the value of the csih_True (if it is false than the value of the csih_False).
        /// </summary>
        /// <param name="key">[in] The key.</param>
        /// <param name="value">[in] The boolean.</param>
        /// <returns>Returns true if the insertion was success. In case an item with same key already exist the function returns false.</returns>
        public bool addBool(string key, bool value)
        {
            if (header.ContainsKey(key))
                return false;

            header.Add(key, (value ? csih_True : csih_False));

            return true;
        }

        /// <summary>
        /// Add a new (key,vale) pair to the header where the value is an integer. The integer will be stored as a string in the header.
        /// </summary>
        /// <param name="key">[in] The key.</param>
        /// <param name="value">[in] The integer.</param>
        /// <returns>Returns true if the insertion was success. In case an item with same key already exist the function returns false.</returns>
        public bool addInt(string key, int value)
        {
            if (header.ContainsKey(key))
                return false;

            header.Add(key, value.ToString());

            return true;
        }

        /// <summary>
        /// It gives back the stored value beside the given key if it is exists.
        /// </summary>
        /// <param name="key">[in] Name of the key.</param>
        /// <param name="value">[out] The stored value.</param>
        /// <returns>Returns true if an item with the given key is exists.</returns>
        public bool get(string key, out string value)
        {
            value = "";
            if (!header.ContainsKey(key))
                return false;

            value = header[key];

            return true;
        }

        /// <summary>
        /// It gives back true in the value parameter only if the stored string was the same as the value of the csih_True.
        /// </summary>
        /// <param name="key">[in] Name of the key.</param>
        /// <param name="value">[out] The stored logical value.</param>
        /// <returns>Returns true if an item with the given key is exists.</returns>
        public bool getBool(string key, ref bool value)
        {
            if (!header.ContainsKey(key))
                return false;

            value = (header[key] == csih_True ? true : false);

            return true;
        }

        /// <summary>
        /// It gives back the stored string converted to integer int the value parameter.
        /// </summary>
        /// <param name="key">[in] Name of the key.</param>
        /// <param name="value">[out] The integer value.</param>
        /// <returns>Returns true if an item with the given key is exists.</returns>
        public bool getInt(string key, ref int value)
        {
            if (!header.ContainsKey(key))
                return false;

            value = Int32.Parse(header[key]);

            return true;
        }

        /// <summary>
        /// It writes out the header into the given file. The file must be opened for writing.
        /// </summary>
        /// <param name="io">[in] The IO containing the file into the header will be written.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if any error happen during the writing.</exception>
        public void save(IO binIo)
        {
            binIo.writeUInt4((uint)(header.Count));
            foreach (KeyValuePair<string, string> entry in header)
            {
                binIo.writeShortString(entry.Key);
                binIo.writeShortString(entry.Value);
            }
        }

        /// <summary>
        /// It reads back the header from the given file. The file must be opened for reading.
        /// </summary>
        /// <param name="io">[in] The IO containing the file from the header will be read.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if any error happen during the reading.</exception>
        public void load(IO binIo)
        {
            uint num = binIo.readUInt4();
            for (int i = 0; i < num; i++)
            {
                string key = binIo.readShortString();
                string value = binIo.readShortString();

                header.Add(key, value);
            }
        }

        public void skipHeader(IO io)
        {
            string csi = io.readString(4);
            uint csiHeaderSize = io.readUInt4();

            for (int i = 0; i < csiHeaderSize; ++i)
            {
                io.vSkip(2);
                ulong skipped = io.readULong8();
                io.vSkip((long)skipped - 8);
            }
        }

        /// <summary>
        /// It prints out the header for debuging.
        /// </summary>
        public void dump()
        {
            foreach (KeyValuePair<string, string> entry in header)
                WriteMsg.WriteLine("[" + entry.Key + "]=[" + entry.Value + "]", WriteMsg.MsgLevel.Debug);
        }

        /// <summary>String representation of the true value.</summary>
        public const string csih_True = "1";

        /// <summary>String representation of the false value.</summary>
        public const string csih_False = "0";

        /// <summary>Constant for the CsiHeader Type string.</summary>
        public const string csih_Type = "Type";

        /// <summary>Constant for the BinaryVersion string.</summary>
        public const string csih_BinaryVersion = "BinaryVersion";

        /// <summary>Constant for the APIVersion string.</summary>
        public const string csih_APIVersion = "APIVersion";

        /// <summary>Constant for the FullAnalysis string.</summary>
        public const string csih_FullAnalysis = "FullAnalysis";

        /// <summary>Constant for the SchemaFilter string.</summary>
        public const string csih_SchemaFilter = "SchemaFilter";

        /// <summary>Constant for the PrecompiledHeader string.</summary>
        public const string csih_PrecompiledHeader = "PrecompiledHeader";

        /// <summary>Constant for the UsePrecompiledHeader string.</summary>
        public const string csih_UsePrecompiledHeader = "UsePrecompileHeader";

        /// <summary>Constant for the NumberOfIncrLinked string.</summary>
        public const string csih_NumOfIncrLinked = "NumberOfIncrLinked";

        /// <summary>Constant for the PreanalyzedIncludesUsed string.</summary>
        public const string csih_PreanalyzedIncludesUsed = "PreanalyzedIncludesUsed";

        /// <summary>Constant for the OriginalLocation string.</summary>
        public const string csih_OriginalLocation = "OriginalLocation";

        /// <summary>Constant for the PsiKind string.</summary>
        public const string csih_PsiKind = "PsiKind";

        /// <summary>Constant for the Language string.</summary>
        public const string csih_Language = "Language";
    }

}