import React from "react";
import Radio from "@material-ui/core/Radio";
import RadioGroup from "@material-ui/core/RadioGroup";
import FormControlLabel from "@material-ui/core/FormControlLabel";
import FormControl from "@material-ui/core/FormControl";
import FormLabel from "@material-ui/core/FormLabel";

export default function RadioButtonsGroup({
  formLabel = "",
  inputLabels = [],
  defaultValue = "",
  ariaLabel = "",
  radioGroupName = "",
}) {
  const [value, setValue] = React.useState(defaultValue);

  const handleChange = (event) => {
    setValue(event.target.value);
  };

  return (
    <FormControl component="fieldset">
      <FormLabel component="legend">{formLabel}</FormLabel>
      <RadioGroup
        aria-label={ariaLabel}
        name={radioGroupName}
        value={value}
        onChange={handleChange}
      >
        {inputLabels.map((il) => (
          <FormControlLabel
            value={il.value}
            control={<Radio />}
            label={il.label}
          />
        ))}
      </RadioGroup>
    </FormControl>
  );
}
