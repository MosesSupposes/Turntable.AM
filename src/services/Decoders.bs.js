// Generated by ReScript, PLEASE EDIT WITH CARE

import * as Json_decode from "@glennsl/bs-json/src/Json_decode.bs.js";

function decodeMetadata(json) {
  return {
          context_description: Json_decode.field("context_description", Json_decode.string, json)
        };
}

function decodeContext(json) {
  return {
          metadata: Json_decode.field("metadata", decodeMetadata, json),
          uri: Json_decode.field("uri", Json_decode.string, json)
        };
}

function decodeImage(json) {
  return {
          url: Json_decode.field("url", Json_decode.string, json),
          height: Json_decode.field("height", Json_decode.$$int, json),
          width: Json_decode.field("width", Json_decode.$$int, json)
        };
}

function decodeAlbum(json) {
  return {
          uri: Json_decode.field("uri", Json_decode.string, json),
          name: Json_decode.field("name", Json_decode.string, json),
          images: Json_decode.field("images", (function (param) {
                  return Json_decode.list(decodeImage, param);
                }), json)
        };
}

function decodeArtist(json) {
  return {
          name: Json_decode.field("name", Json_decode.string, json),
          uri: Json_decode.field("uri", Json_decode.string, json)
        };
}

function decodeCurrentTrack(json) {
  return {
          album: Json_decode.field("album", decodeAlbum, json),
          artists: Json_decode.field("artists", (function (param) {
                  return Json_decode.list(decodeArtist, param);
                }), json),
          id: Json_decode.field("id", Json_decode.string, json),
          media_type: Json_decode.field("media_type", Json_decode.string, json),
          name: Json_decode.field("name", Json_decode.string, json),
          type_: Json_decode.field("type", Json_decode.string, json),
          uri: Json_decode.field("uri", Json_decode.string, json)
        };
}

function decodeTrackWindow(json) {
  return {
          current_track: Json_decode.field("current_track", decodeCurrentTrack, json),
          next_tracks: Json_decode.field("next_tracks", (function (param) {
                  return Json_decode.list(decodeCurrentTrack, param);
                }), json),
          previous_tracks: Json_decode.field("previous_tracks", (function (param) {
                  return Json_decode.list((function (param) {
                                return Json_decode.optional(decodeCurrentTrack, param);
                              }), param);
                }), json)
        };
}

function decodeTrackInfo(json) {
  return {
          context: Json_decode.field("context", decodeContext, json),
          duration: Json_decode.field("duration", Json_decode.$$int, json),
          position: Json_decode.field("position", Json_decode.$$float, json),
          paused: Json_decode.field("paused", Json_decode.bool, json),
          shuffle: Json_decode.field("shuffle", Json_decode.bool, json),
          track_window: Json_decode.field("track_window", decodeTrackWindow, json)
        };
}

var MusicPlayer = {
  decodeMetadata: decodeMetadata,
  decodeContext: decodeContext,
  decodeImage: decodeImage,
  decodeAlbum: decodeAlbum,
  decodeArtist: decodeArtist,
  decodeCurrentTrack: decodeCurrentTrack,
  decodeTrackWindow: decodeTrackWindow,
  decodeTrackInfo: decodeTrackInfo
};

function decodeFollowers(json) {
  return {
          href: Json_decode.field("href", (function (param) {
                  return Json_decode.optional(Json_decode.string, param);
                }), json),
          total: Json_decode.field("total", Json_decode.$$int, json)
        };
}

function decodeUser(json) {
  return {
          country: Json_decode.field("country", Json_decode.string, json),
          display_name: Json_decode.field("display_name", Json_decode.string, json),
          email: Json_decode.field("email", Json_decode.string, json),
          followers: Json_decode.field("followers", decodeFollowers, json),
          href: Json_decode.field("href", Json_decode.string, json),
          id: Json_decode.field("id", Json_decode.string, json),
          images: Json_decode.field("images", (function (param) {
                  return Json_decode.array((function (param) {
                                return Json_decode.optional(Json_decode.string, param);
                              }), param);
                }), json)
        };
}

var Profile = {
  decodeFollowers: decodeFollowers,
  decodeUser: decodeUser
};

export {
  MusicPlayer ,
  Profile ,
  
}
/* No side effect */
