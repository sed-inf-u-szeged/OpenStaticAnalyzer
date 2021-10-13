// This file contains the Data Transfer Objects used for serializing Diagnostics to XML

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Xml.Serialization;
using Microsoft.CodeAnalysis;

namespace Columbus.CSAN.Diagnostics
{
    [Serializable]
    public class Diagnostic
    {
        [XmlAttribute]
        public string Id;
        [XmlAttribute]
        public string Severity;
        [XmlAttribute]
        public bool IsSuppressed;
        [XmlAttribute]
        public string Message;

        public Location Location;
        public Descriptor Descriptor;

        public Diagnostic()
        {
        }

        public Diagnostic(Microsoft.CodeAnalysis.Diagnostic diagnostic, FileLinePositionSpan lineSpan, string filePath)
        {
            Id = diagnostic.Id;
            Severity = diagnostic.Severity.ToString();
            IsSuppressed = diagnostic.IsSuppressed;
            Message = diagnostic.GetMessage(CultureInfo.InvariantCulture);
            Descriptor = new Descriptor
            {
                Title = diagnostic.Descriptor.Title.ToString(CultureInfo.InvariantCulture),
                Category = diagnostic.Descriptor.Category,
                Description = diagnostic.Descriptor.Description.ToString(CultureInfo.InvariantCulture),
                HelpLinkUri = diagnostic.Descriptor.HelpLinkUri,
                CustomTags = diagnostic.Descriptor.CustomTags.ToList()
            };

            if (filePath != null)
            {
                Location = new Location
                {
                    FilePath = filePath,
                    StartLine = lineSpan.StartLinePosition.Line + 1,
                    StartCharacter = lineSpan.StartLinePosition.Character + 1,
                    EndLine = lineSpan.EndLinePosition.Line + 1,
                    EndCharacter = lineSpan.EndLinePosition.Character + 1
                };
            }
        }
    }

    [Serializable]
    public class Location
    {
        [XmlAttribute]
        public string FilePath;
        [XmlAttribute]
        public int StartLine;
        [XmlAttribute]
        public int StartCharacter;
        [XmlAttribute]
        public int EndLine;
        [XmlAttribute]
        public int EndCharacter;
    }

    [Serializable]
    public class Descriptor
    {
        [XmlAttribute]
        public string Title;
        [XmlAttribute]
        public string Category;
        [XmlAttribute]
        public string Description;
        [XmlAttribute]
        public string HelpLinkUri;

        [XmlArrayItem("Tag")]
        public List<string> CustomTags;
    }
}
