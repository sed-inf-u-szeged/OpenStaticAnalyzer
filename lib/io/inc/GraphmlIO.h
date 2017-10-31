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

#ifndef _GRAPHMLIO_H_
#define _GRAPHMLIO_H_

#include <io/inc/ioBase.h>
#include <io/inc/SimpleXmlIO.h>

/**
 * \file GraphmlIO.h
 * \brief Contains GraphmlIO declaration
 */

namespace columbus {
    namespace io {

        class GraphmlIO : virtual public IOBase {
        public:

            typedef enum {
                ls_line,
                ls_dashed,
                ls_dotted,
                ls_dashed_dotted
            } LineStyle;

            typedef enum {
                at_standard,
                at_delta,
                at_diamond,
                at_white_diamond,
                at_white_delta,
                at_none,
                at_plain,
                at_concave,
                at_convex,
                at_circle,
                at_dash,
                at_transparent_circle,
                at_skewed_dash,
                at_t_shape
            } ArrowType;

        public:
            GraphmlIO(const std::string& filename, const std::string& graphName, const std::string& encoding = "UTF-8");
            ~GraphmlIO();

            void writeEdge(const std::string& fromNodeId, const std::string& toNodeId, const std::string& edgeLabel, const float width, const LineStyle lineStyle, const ArrowType sourceArrowType, const ArrowType targetArrowType);
            void writeEdgeBuffer(const std::string& fromNodeId, const std::string& toNodeId, const std::string& edgeLabel, const float width, const LineStyle lineStyle, const ArrowType sourceArrowType, const ArrowType targetArrowType);
            void writeEdgeBufferFlush();
            void writeNode(const std::string& nodeId, const std::string& title, const std::string& content, const std::string& titleBGColor, const std::string& groupId = "", const std::string& fillColor = "#CCCCFF");
            void writeCGNode(const std::string& nodeId, const std::string& title, const std::string& titleBGColor, const std::string& textColor = "#000000", const std::string& shape = "ellipse");
            void writeGroupBegin(const std::string& groupId, const std::string& groupName, const std::string& fillColor = "#F2F0D8");
            void writeGroupEnd();
            void writeGroupNodeBegin(const std::string& nodeId, const std::string& title, const std::string& content, const std::string& titleBGColor, const std::string& groupId = "", const std::string& fillColor = "#CCCCFF");
            void writeGroupNodeEnd();
            void setNodeTitleFamily(const std::string& font);
            void setNodeContentFamily(const std::string& font);
            void setCharacterWithMultiplier(int multiplier);
            void setCharacterHeightMultiplier(int multiplier);
        private:
            SimpleXmlIO output;
            int edgeCounter;
            std::string titleFont;
            std::string contentFont;
            int characterWithMultiplier;
            int characterHeightMultiplier;

            static const char* ArrowTypeToString(const ArrowType arrowType);
            static const char* LineStypeToString(const LineStyle lineStyle);

            struct edge_meta{
              std::string fromNodeId;
              std::string toNodeId;
              std::string edgeLabel;
              float width;
              LineStyle lineStyle;
              ArrowType sourceArrowType;
              ArrowType targetArrowType;
            };
            std::list<edge_meta> edgeBuffer;

        };
    }
}



#endif
