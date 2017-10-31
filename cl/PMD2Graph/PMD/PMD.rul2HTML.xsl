<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:template match="/">
      <html>
        <head>
          <title>
            <xsl:value-of disable-output-escaping="yes" select="Rul/ToolDescription/Configuration/ToolDescriptionItem"/>
          </title>
        </head>
        <body>
          <xsl:apply-templates select="Rul"/>
        </body>
      </html>
  </xsl:template>


  <xsl:template match="Rul">
    <xsl:for-each select="Metric">
      <xsl:if test="Configuration/@name='Default'">
        <xsl:if test="Configuration/Enabled='false'">
          <font color="red">
            <h2>
              <xsl:value-of disable-output-escaping="yes" select="@id"/>
            </h2>
            <ul>
              <li>
                DisplayName: <b>
                  <xsl:value-of disable-output-escaping="yes" select="Configuration/Language/DisplayName"/>
                </b>
              </li>
              <li>
                HelpText: <xsl:value-of disable-output-escaping="yes" select="Configuration/Language/HelpText"/>
              </li>
            </ul>
          </font>
        </xsl:if>

        <xsl:if test="Configuration/Enabled='true'">
          <h2>      
            <xsl:value-of disable-output-escaping="yes" select="@id"/>
          </h2>
          <ul>
            <li>
              DisplayName: <b>
                <xsl:value-of disable-output-escaping="yes" select="Configuration/Language/DisplayName"/>
              </b>
            </li>
            <li>
              HelpText: <xsl:value-of disable-output-escaping="yes" select="Configuration/Language/HelpText"/>
            </li>
          </ul>
        </xsl:if>

      </xsl:if>
    </xsl:for-each>
  </xsl:template>

</xsl:stylesheet>
