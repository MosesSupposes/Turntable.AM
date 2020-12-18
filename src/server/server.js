const express = require("express");
const cors = require("cors");
const querystring = require("querystring");
const { v4: uuid } = require("uuid");
const PORT = 9000;
const axios = require("axios");

const clientId = "96e25e1a56b5467fbbf82af545444904";
// const clientSecret = "is it secret, is it safe?";
const clientSecret = "c464321f843d40cd88929d6edfbfe1cf";
// const redirectUri = "http://localhost:1234";
const redirectUri = "https://kind-fermat-94e8ea.netlify.app/";

const generateRandomString = () => uuid();

const server = express();
server.use(cors());

// server.get("/login", (req, res) => {
// 	const state = generateRandomString();
// 	const scope = [
// 		"playlist-modify-public", // used to get write access to a user's public playlists
// 		"playlist-modify-private", // used to get write access to a user's private playlists
// 		"playlist-read-private", // used to get read access to user's private playlists
// 		"playlist-read-collaborative", // used to include collaborative playlists when requesting a user's playlists
// 		"user-read-recently-played", // used to get current user's recently played tracks
// 		"user-top-read", //used to get a user's top artists and tracks
// 		"ugc-image-upload", // used to upload a custom playlist cover image
// 		"user-follow-read", // used to get read access to the list of artists and other users that the user follows
// 		"user-library-read", // used to get read access to a user's "Your Music" library
// 		"user-library-modify", // used to get write/delete access to a user's "Your Music" library (can be used to save tracks + albums for current user)
// 		"user-read-email", // used to get read access to user's email address (can be used to get the current user's profile)
// 		"user-read-private", // used to get read access to a user's subscription details (type of user account) (can be used to search for an item; i.e. a song or album)
// 	].join(" ");
// 	res.redirect(
// 		"https://accounts.spotify.com/authorize?" +
// 			querystring.stringify({
// 				response_type: "code",
// 				client_id: clientId,
// 				scope: scope,
// 				redirect_uri: redirectUri,
// 				state: state,
// 			})
// 	);
// });

server.get("/login", async (req, res) => {
	const base64EncodedClientId = Buffer.from(clientId).toString(
		"base64"
	);
	try {
		const response = await axios.post(
			"https://accounts.spotify.com/api/token",
			{
				grant_type: "client_credentials",
			},
			{
				headers: {
					"Content-Type": "application/x-www-form-urlencoded",
					Authorization: `Basic ${base64EncodedClientId}:${clientSecret}`,
				},
			}
		);
		console.log(response);
		res.status(200).json(response);
		console.log(fetch);
	} catch (err) {
		res.status(500).send("failed to fetch");
		console.error("Here", err);
	}
});

server.get("/access_token", (req, res) => {});

server.listen(PORT, () =>
	console.log("Server running on port " + PORT)
);
