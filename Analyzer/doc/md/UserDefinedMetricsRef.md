## The UserDefinedMetrics module

In addition to the built-in metrics, users can create their own metrics by using the UserDefinedMetrics (UDM) module.
These new metrics can be established with a formula that can use any previous OpenStaticAnalyzer metric and can even depend on other custom user-defined metrics.

### Defining a metric

- Metric definitions are surrounded by a `<tool name = "UDM" enabled = "true"></tool>` tag.
- Metrics are defined using a `<udm id = "NAME"></udm>` tag.
    - `NAME` follows standard identifier conventions (starts with a letter or an underscore, followed by any number of letters, numbers, or underscores).
    - `pi`, `epsilon`, and `inf` are occupied names (in a case-insensitive manner, so `Pi`, `pI`, `Epsilon`, `epSiloN`, etc. are occupied as well).
- Each metric definition can contain multiple configurations using a `<configuration name = "ConfigName"></configuration>` tag.
    - The `Default` configuration is mandatory, while the language-specific "overrides" are optional.
    - Each "override" inherits its starting setting values from the `Default` configuration.
    - The valid language-specific configuration values (at the moment) are `cpp`, `csharp`, `java`, `javascript`, `python`, and `rpg`.
- Each configuration can contain the following settings:
    - `description`: The description of the metric (default: "").
    - `display-name`: An optional name, if something other than the ID should be used for display (default: "").
    - `help-text`: Additional help text for the metric (default: "").
    - `formula`: The formula used to calculate the value of the metric. It can be any valid expression supported by the [ExprTk library](https://exprtk.codeplex.com/) and contain references to any previously computed metrics (e.g., LLOC, NOS, CBO, etc.).
    - `type`: The desired output type of the formula (valid values: "Integer", "Float"; default: "Float").
    - `calculated`: This field contains a list of syntactic element types (e.g., Class, Method, etc.) the metric is calculated for inside `<calculated-for>` tags. See the example below.
        - Note that every (both built-in and user-defined) metric has a unique set of elements it is computed for. Therefore, if a metric is dependent on another, its `<calculated-for>` set should be a subset of the dependency's for it to be universally computable.

### Example profile.xml

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.xml}
<?xml version="1.0" encoding="UTF-8"?>
<analyzer-profile>
  <tool-options>
    <tool name = "UDM" enabled = "true">
      <udm id = "UDM_test_metric">
        <configuration name = "Default">
          <description>Blablabla</description>
          <display-name>UDM Test Metric</display-name>
          <help-text>A helpful comment</help-text>
          <formula>LLOC + 1 + sin(pi)^3</formula>
          <type>Integer</type>
          <calculated>
            <calculated-for>Class</calculated-for>
            <calculated-for>Method</calculated-for>
          </calculated>
        </configuration>
      </udm>
    </tool>
  </tool-options>
</analyzer-profile>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
