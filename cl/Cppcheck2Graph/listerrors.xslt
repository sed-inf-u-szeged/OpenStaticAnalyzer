<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
    <xsl:for-each select="results/errors/error">
	<xsl:sort select="@id"/>
        <xsl:value-of select="@id"/>|<xsl:value-of select="@msg"/><xsl:text>&#10;</xsl:text>
    </xsl:for-each>
</xsl:template>

</xsl:stylesheet>
