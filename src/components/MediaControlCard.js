import React from "react";
import { makeStyles, useTheme } from "@material-ui/core/styles";
import Card from "@material-ui/core/Card";
import CardContent from "@material-ui/core/CardContent";
import CardMedia from "@material-ui/core/CardMedia";
import IconButton from "@material-ui/core/IconButton";
import Typography from "@material-ui/core/Typography";
import SkipPreviousIcon from "@material-ui/icons/SkipPrevious";
import PlayArrowIcon from "@material-ui/icons/PlayArrow";
import PauseIcon from "@material-ui/icons/Pause";
import SkipNextIcon from "@material-ui/icons/SkipNext";

const useStyles = makeStyles((theme) => ({
  root: {
    display: "flex",
    backgroundImage: "linear-gradient(to right, white, #191414)",
  },
  details: {
    display: "flex",
    flexDirection: "column",
  },
  content: {
    flex: "1 0 auto",
  },
  cover: {
    width: 151,
  },
  contros: {
    display: "flex",
    alignItems: "center",
    paddingLeft: theme.spacing(1),
    paddingBottom: theme.spacing(1),
    cursor: "pointer",
  },
  playIcon: {
    height: 38,
    width: 38,
  },
}));

const togglePlay = (player) => {
  return player.togglePlay();
};

const skipToNextTrack = (player) => {
  return player.nextTrack();
};

const skipToPreviousTrack = (player) => {
  return player.previousTrack();
};

export default function MediaControlCard({
  songTitle,
  artist,
  albumCoverUrl,
  albumName,
  player,
  isPaused,
}) {
  const classes = useStyles();
  const theme = useTheme();

  return (
    <Card className={classes.root}>
      <div className={classes.details}>
        <CardContent className={classes.content}>
          <Typography component="h5" variant="h5">
            {songTitle}
          </Typography>
          <Typography variant="subtitle1" color="textSecondary">
            {artist}
          </Typography>
        </CardContent>
        <div className={classes.controls}>
          <IconButton
            aria-label="previous"
            onClick={() => skipToPreviousTrack(player)}
          >
            <SkipPreviousIcon />
          </IconButton>
          <IconButton
            aria-label="play/pause"
            onClick={(_) => togglePlay(player)}
          >
            {isPaused ? (
              <PlayArrowIcon className={classes.playIcon} />
            ) : (
              <PauseIcon className={classes.playIcon} />
            )}
          </IconButton>
          <IconButton aria-label="next" onClick={() => skipToNextTrack(player)}>
            <SkipNextIcon />
          </IconButton>
        </div>
      </div>
      <CardMedia
        className={classes.cover}
        image={albumCoverUrl}
        title={albumName}
      />
    </Card>
  );
}
