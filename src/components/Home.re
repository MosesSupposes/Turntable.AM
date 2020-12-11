open ReactNative;
open UsePage;

let styles =
  Style.(StyleSheet.create({"header": style(~marginTop=40.->dp, ())}));

[@react.component]
let make = (~setPage: (Page.t => Page.t) => unit) => {
  <View style={styles##header}>
    <Text> {React.string("Welcome to Turntable.Am")} </Text>
  </View>;
};
