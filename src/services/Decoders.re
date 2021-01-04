module MusicPlayer = {
  type metadata = {context_description: string};
  type context = {
    metadata,
    uri: string,
  };
  type image = {
    url: string,
    height: int,
    width: int,
  };
  type album = {
    uri: string,
    name: string,
    images: list(image),
  };
  type artist = {
    name: string,
    uri: string,
  };
  type current_track = {
    album,
    artists: list(artist),
    id: string,
    media_type: string,
    name: string,
    type_: string,
    uri: string,
  };
  type track_window = {
    current_track,
    next_tracks: list(current_track),
    // previous_tracks might be an empty array
    previous_tracks: list(option(current_track)),
  };
  type trackInfo = {
    context,
    duration: int,
    position: float,
    paused: bool,
    shuffle: bool,
    track_window,
  };

  let decodeMetadata = json => {
    Json.Decode.{
      context_description: json |> field("context_description", string),
    };
  };

  let decodeContext = json => {
    Json.Decode.{
      metadata: json |> field("metadata", decodeMetadata),
      uri: json |> field("uri", string),
    };
  };

  let decodeImage = json => {
    Json.Decode.{
      url: json |> field("url", string),
      height: json |> field("height", int),
      width: json |> field("width", int),
    };
  };

  let decodeAlbum = json => {
    Json.Decode.{
      uri: json |> field("uri", string),
      name: json |> field("name", string),
      images: json |> field("images", list(decodeImage)),
    };
  };

  let decodeArtist = json => {
    Json.Decode.{
      name: json |> field("name", string),
      uri: json |> field("uri", string),
    };
  };

  let decodeCurrentTrack = json => {
    Json.Decode.{
      album: json |> field("album", decodeAlbum),
      artists: json |> field("artists", list(decodeArtist)),
      id: json |> field("id", string),
      media_type: json |> field("media_type", string),
      name: json |> field("name", string),
      type_: json |> field("type", string),
      uri: json |> field("uri", string),
    };
  };

  let decodeTrackWindow = json => {
    Json.Decode.{
      current_track: json |> field("current_track", decodeCurrentTrack),
      next_tracks: json |> field("next_tracks", list(decodeCurrentTrack)),
      previous_tracks:
        json |> field("previous_tracks", list(optional(decodeCurrentTrack))),
    };
  };

  let decodeTrackInfo = json => {
    Json.Decode.{
      context: json |> field("context", decodeContext),
      duration: json |> field("duration", int),
      position: json |> field("position", float),
      paused: json |> field("paused", bool),
      shuffle: json |> field("shuffle", bool),
      track_window: json |> field("track_window", decodeTrackWindow),
    };
  };
};
