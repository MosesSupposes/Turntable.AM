// Generated by ReScript, PLEASE EDIT WITH CARE

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_exceptions from "bs-platform/lib/es6/caml_exceptions.js";
import * as Footer$Turntableam from "./Footer.bs.js";
import * as Header$Turntableam from "./Header.bs.js";
import * as UsePage$Turntableam from "../hooks/UsePage.bs.js";
import * as ParseUrl$Turntableam from "../services/ParseUrl.bs.js";
import * as SpotifyAPI$Turntableam from "../services/SpotifyAPI.bs.js";
import * as ApplicationContainer$Turntableam from "./ApplicationContainer.bs.js";

function App(Props) {
  var match = UsePage$Turntableam.make(undefined);
  var setPage = match.setPage;
  var match$1 = React.useState(function () {
        
      });
  var setAccessToken = match$1[1];
  var MissingAccessToken = Caml_exceptions.create("MissingAccessToken");
  React.useEffect((function () {
          var accessToken = ParseUrl$Turntableam.getAccessToken(document.location.href);
          Curry._1(setAccessToken, (function (param) {
                  return accessToken;
                }));
          if (accessToken !== undefined) {
            SpotifyAPI$Turntableam.Search.searchArtist(accessToken, "Future", (function (future) {
                    return Promise.resolve((console.log(future), undefined));
                  }), (function (error) {
                    return Promise.resolve((console.log(error), undefined));
                  }));
          } else {
            Promise.resolve(undefined);
          }
          if (accessToken !== undefined) {
            SpotifyAPI$Turntableam.Search.searchTrack(accessToken, "money%20longer", (function (tracksPromise) {
                    console.log(tracksPromise);
                    return tracksPromise;
                  }), (function (error) {
                    console.log(error);
                    return Promise.resolve(undefined);
                  }));
          } else {
            Promise.reject({
                  RE_EXN_ID: MissingAccessToken
                });
          }
          if (accessToken !== undefined) {
            SpotifyAPI$Turntableam.Profile.getCurrentUsersProfile(accessToken);
          } else {
            Promise.reject({
                  RE_EXN_ID: MissingAccessToken
                });
          }
          
        }), []);
  return React.createElement("main", undefined, React.createElement(Header$Turntableam.make, {
                  setPage: setPage
                }), React.createElement(ApplicationContainer$Turntableam.make, {
                  page: match.page,
                  setPage: setPage,
                  accessToken: match$1[0]
                }), React.createElement(Footer$Turntableam.make, {}));
}

var make = App;

export {
  make ,
  
}
/* react Not a pure module */
