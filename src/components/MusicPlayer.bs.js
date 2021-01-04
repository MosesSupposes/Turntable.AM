// Generated by ReScript, PLEASE EDIT WITH CARE

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Decoders$Turntableam from "../services/Decoders.bs.js";

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

var Helpers = {
  getCurrentTrack: getCurrentTrack,
  getArtistOrUnknown: getArtistOrUnknown,
  getCurrentArtist: getCurrentArtist,
  getCurrentAlbum: getCurrentAlbum
};

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
                                deviceId: prevState.deviceId,
                                spotifyPlayer: prevState.spotifyPlayer,
                                trackInfo: decodedTrackInfo
                              };
                      }));
        }));
  
}

function renderLoadingScreen(param) {
  return React.createElement("p", undefined, "Loading...");
}

function renderConnectionInstructions(param) {
  return React.createElement("p", undefined, "To interact with the Music Player, navigate to Spotify from your web browser and click the \"Connect to a device\" button. Then, select \"Turntable.AM\" from the menu.");
}

function MusicPlayer(Props) {
  var setPage = Props.setPage;
  var match = React.useState(function () {
        return {
                currentTrack: "",
                currentArtist: "",
                currentAlbum: "",
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
  React.useEffect((function () {
          if (trackInfo !== undefined) {
            console.log("here", trackInfo);
          }
          
        }), [trackInfo]);
  if (spotifyPlayer !== undefined) {
    if (trackInfo !== undefined) {
      return React.createElement("div", undefined, React.createElement("h2", undefined, "Now Playing:"), React.createElement("p", undefined, "Track: " + musicPlayer.currentTrack + " "), React.createElement("p", undefined, "Artist: " + musicPlayer.currentArtist), React.createElement("p", undefined, "Album: " + musicPlayer.currentAlbum));
    } else {
      return renderConnectionInstructions(undefined);
    }
  } else {
    return renderLoadingScreen(undefined);
  }
}

var make = MusicPlayer;

export {
  Helpers ,
  createEventHandlers ,
  renderLoadingScreen ,
  renderConnectionInstructions ,
  make ,
  
}
/* react Not a pure module */
