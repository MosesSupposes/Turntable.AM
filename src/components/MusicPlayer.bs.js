// Generated by ReScript, PLEASE EDIT WITH CARE

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";

function MusicPlayer(Props) {
  var match = React.useState(function () {
        return {
                currentTrack: "",
                currentArtist: "",
                currentAlbum: "",
                spotifyPlayer: undefined
              };
      });
  var setMusicPlayer = match[1];
  var musicPlayer = match[0];
  React.useEffect((function () {
          setTimeout((function (param) {
                  return Curry._1(setMusicPlayer, (function (prevState) {
                                return {
                                        currentTrack: prevState.currentTrack,
                                        currentArtist: prevState.currentArtist,
                                        currentAlbum: prevState.currentAlbum,
                                        spotifyPlayer: Caml_option.some(window.player)
                                      };
                              }));
                }), 1000);
          
        }), []);
  if (musicPlayer.spotifyPlayer !== undefined) {
    return React.createElement("div", undefined, React.createElement("h2", undefined, "Now Playing:"), React.createElement("p", undefined, "Track: " + musicPlayer.currentTrack + " "), React.createElement("p", undefined, "Artist: " + musicPlayer.currentArtist), React.createElement("p", undefined, "Album: " + musicPlayer.currentAlbum));
  } else {
    return React.createElement("p", undefined, "Loading...");
  }
}

var make = MusicPlayer;

export {
  make ,
  
}
/* react Not a pure module */
