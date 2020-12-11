// This type is a two-dimensional list where each sublist contains n number of songs(of type Batch.batch) where n = number of DJs in a given room.
type mergedPlaylist = array(Batch.t);

type state = {
  currentSong: option(Song.t),
  nextSong: option(Song.t),
  currentDj: option(User.t),
  currentBatchIndex: int,
  currentSongIndex: int,
  mergedPlaylist,
  individualPlaylists: list(Playlist.t),
};

type action =
  | EnqueueNextBatch
  | EnqueueNextSong
  | AddSong(Playlist.t, Song.t);

type export = {
  mergedPlaylist,
  individualPlaylists: list(Playlist.t),
  currentSong: option(Song.t),
  nextSong: option(Song.t),
  currentDj: option(User.t),
};

let reducer = (state, action) => {
  switch (action) {
  // Reset the mergedPlaylist to the beginning if it reaches the end. Otherwise, increment the batch index by 1.
  | EnqueueNextBatch => {
      ...state,
      currentBatchIndex:
        state.currentBatchIndex + 1 == Belt.Array.length(state.mergedPlaylist)
          ? 0 : state.currentBatchIndex + 1,
    }
  // Same logic as EnqueeeNextBatch: reset the index to the first song in the next batch if the end of the current batch is reached; otherwise, increment the song index.
  | EnqueueNextSong => {
      ...state,
      currentSongIndex:
        state.currentSongIndex
        + 1
        == Belt.Array.length(state.mergedPlaylist[state.currentBatchIndex])
          ? 0 : state.currentSongIndex + 1,
    }
  | AddSong(playlist, song) => {
      ...state,
      individualPlaylists:
        List.map(
          (pl: Playlist.t): Playlist.t =>
            if (pl.dj === playlist.dj) {
              {...pl, songs: pl.songs @ [song]};
            } else {
              pl;
            },
          state.individualPlaylists,
        ),
    }
  };
};

let initialState = {
  currentSong: None,
  nextSong: None,
  currentDj: None,
  currentBatchIndex: 0,
  currentSongIndex: 0,
  mergedPlaylist: [||],
  individualPlaylists: [],
};

let make = (playlist: Playlist.t): export => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  {
    mergedPlaylist: state.mergedPlaylist,
    individualPlaylists: state.individualPlaylists,
    currentSong: state.currentSong,
    nextSong: state.nextSong,
    currentDj: state.currentDj,
  };
};
