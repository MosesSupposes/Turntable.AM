type t = {
  id: string,
  djs: string,
  songQueue: list(Batch.t),
  playlists: list(Playlist.t),
  currentSong: Song.t,
  currentDJ: User.t,
};
