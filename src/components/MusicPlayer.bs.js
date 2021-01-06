// Generated by ReScript, PLEASE EDIT WITH CARE

import * as List from "bs-platform/lib/es6/list.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Decoders$Turntableam from "../services/Decoders.bs.js";
import MediaControlCardJs from "./MediaControlCard.js";

((require("../styles/musicPlayer.css")));

function getCurrentTrack(trackInfo) {
  return trackInfo.track_window.current_track.name;
}

function getArtistOrUnknown(artists) {
  if (!artists) {
    return "Unknown";
  }
  var artist = artists.hd;
  return artist.name;
}

function getCurrentArtist(trackInfo) {
  return getArtistOrUnknown(trackInfo.track_window.current_track.artists);
}

function getCurrentAlbum(trackInfo) {
  return trackInfo.track_window.current_track.album.name;
}

function getNextSong(trackInfo) {
  return List.hd(trackInfo.track_window.next_tracks).name;
}

function getNextArtist(trackInfo) {
  return getArtistOrUnknown(List.hd(trackInfo.track_window.next_tracks).artists);
}

function getAlbumCoverUrl(images) {
  if (!images) {
    return "";
  }
  var restImgs = images.tl;
  if (!restImgs) {
    return images.hd.url;
  }
  var restImgs$1 = restImgs.tl;
  if (restImgs$1) {
    return restImgs$1.hd.url;
  } else {
    return restImgs.hd.url;
  }
}

function createEventHandlers(player, setPage, setMusicPlayer) {
  player.on("initialization_error", (function (e) {
          console.log(e);
          
        }));
  player.on("authentication_error", (function (e) {
          return Curry._1(setPage, (function (param) {
                        return /* Login */2;
                      }));
        }));
  player.on("account_error", (function (e) {
          console.log(e);
          
        }));
  player.on("playback_error", (function (e) {
          console.log(e);
          
        }));
  player.on("player_state_changed", (function (state) {
          var decodedTrackInfo = Decoders$Turntableam.MusicPlayer.decodeTrackInfo(state);
          return Curry._1(setMusicPlayer, (function (prevState) {
                        return {
                                currentTrack: decodedTrackInfo.track_window.current_track.name,
                                currentArtist: getCurrentArtist(decodedTrackInfo),
                                currentAlbum: getCurrentAlbum(decodedTrackInfo),
                                nextSong: getNextSong(decodedTrackInfo),
                                nextArtist: getNextArtist(decodedTrackInfo),
                                deviceId: prevState.deviceId,
                                spotifyPlayer: prevState.spotifyPlayer,
                                trackInfo: decodedTrackInfo
                              };
                      }));
        }));
  
}

function renderLoadingScreen(param) {
  return React.createElement("p", {
              className: "loading"
            }, "Loading...");
}

function renderConnectionInstructions(param) {
  return React.createElement("p", {
              className: "connection-instructions"
            }, "To interact with the Music Player, navigate to Spotify from your web browser and click the \"Connect to a device\" button. Then, select \"Turntable.AM\" from the menu.");
}

var Helpers = {
  getCurrentTrack: getCurrentTrack,
  getArtistOrUnknown: getArtistOrUnknown,
  getCurrentArtist: getCurrentArtist,
  getCurrentAlbum: getCurrentAlbum,
  getNextSong: getNextSong,
  getNextArtist: getNextArtist,
  getAlbumCoverUrl: getAlbumCoverUrl,
  createEventHandlers: createEventHandlers,
  renderLoadingScreen: renderLoadingScreen,
  renderConnectionInstructions: renderConnectionInstructions
};

var make = MediaControlCardJs;

var MediaControlCard = {
  make: make
};

function MusicPlayer(Props) {
  var setPage = Props.setPage;
  var match = React.useState(function () {
        return {
                currentTrack: "",
                currentArtist: "",
                currentAlbum: "",
                nextSong: "",
                nextArtist: "",
                deviceId: undefined,
                spotifyPlayer: undefined,
                trackInfo: undefined
              };
      });
  var musicPlayer = match[0];
  var trackInfo = musicPlayer.trackInfo;
  var spotifyPlayer = musicPlayer.spotifyPlayer;
  var setMusicPlayer = match[1];
  React.useEffect((function () {
          setTimeout((function (param) {
                  return Curry._1(setMusicPlayer, (function (prevState) {
                                return {
                                        currentTrack: prevState.currentTrack,
                                        currentArtist: prevState.currentArtist,
                                        currentAlbum: prevState.currentAlbum,
                                        nextSong: prevState.nextSong,
                                        nextArtist: prevState.nextArtist,
                                        deviceId: window.deviceId,
                                        spotifyPlayer: Caml_option.some(window.player),
                                        trackInfo: prevState.trackInfo
                                      };
                              }));
                }), 1000);
          
        }), []);
  React.useEffect((function () {
          if (spotifyPlayer !== undefined) {
            createEventHandlers(Caml_option.valFromOption(spotifyPlayer), setPage, setMusicPlayer);
          }
          
        }), [spotifyPlayer]);
  if (spotifyPlayer === undefined) {
    return renderLoadingScreen(undefined);
  }
  if (trackInfo === undefined) {
    return renderConnectionInstructions(undefined);
  }
  var albumCoverUrl = getAlbumCoverUrl(trackInfo.track_window.current_track.album.images);
  return React.createElement("div", undefined, React.createElement("h2", undefined, "Now Playing:"), React.createElement("div", {
                  className: "media-control-card-container"
                }, React.createElement(make, {
                      songTitle: musicPlayer.currentTrack,
                      artist: musicPlayer.currentArtist,
                      albumCoverUrl: albumCoverUrl,
                      albumName: musicPlayer.currentAlbum
                    })), React.createElement("p", undefined, "Up Next: " + musicPlayer.nextSong + " by " + musicPlayer.nextArtist));
}

var make$1 = MusicPlayer;

export {
  Helpers ,
  MediaControlCard ,
  make$1 as make,
  
}
/*  Not a pure module */
