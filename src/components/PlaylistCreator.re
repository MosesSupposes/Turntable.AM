//TODO: pass the form control state down to the RadioButtonsGroup component so that the form coming from this parent component can communicate with its child form controls
module RadioButtonsGroup = {
  [@bs.module "./RadioButtonsGroup.js"] [@react.component]
  external make:
    (
      ~radioGroupName: string,
      ~formLabel: string,
      ~inputLabels: array(Js.t({..})),
      ~defaultValue: string,
      ~ariaLabel: string
    ) =>
    React.element =
    "default";
};

// TODO: Move the renderPlaylistEditForm logic into its own component
module Helpers = {
  let handleSubmit = event => {
    Js.log("Playlist created");
  };

  let renderPlaylistCreationForm = () =>
    <form onSubmit=handleSubmit>
      <RadioButtonsGroup
        radioGroupName="visibility"
        formLabel="Visibility"
        inputLabels=[|
          {"value": "public", "label": "Public"},
          {"value": "private", "label": "Private"},
        |]
        defaultValue="public"
        ariaLabel="Playlist visibility"
      />
      <button role="submit"> {React.string("Create")} </button>
    </form>;
};

[@react.component]
let make = () => {
  let (shouldShowPlaylistCreationForm, setShouldShowPlaylistCreationForm) =
    React.useState(() => false);
  let (shouldShowPlayistEditForm, setShouldShowPlaylistEditForm) =
    React.useState(() => false);
  <div>
    <div>
      <button
        onClick={_ =>
          setShouldShowPlaylistCreationForm(prevState => !prevState)
        }>
        {React.string("Create a Playlist")}
      </button>
    </div>
    <div> <p> {React.string("-- Or --")} </p> </div>
    <div>
      <button
        onClick={_ => setShouldShowPlaylistEditForm(prevState => !prevState)}>
        {React.string("Edit a friend's playlist")}
      </button>
    </div>
    {shouldShowPlaylistCreationForm
       ? Helpers.renderPlaylistCreationForm() : <div />}
    {shouldShowPlayistEditForm ? Helpers.renderPlaylistEditForm() : <div />}
  </div>;
  // TODO: Add a "+" icon next to the "Create a Playlist" button
  // TODO: add regular input fields for the playlist name and description
};
