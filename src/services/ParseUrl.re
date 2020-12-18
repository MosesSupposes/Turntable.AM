type parsedUrl = {
  accessToken: string,
  state: string,
};

let parseQueryParams = (queryParams: string): option(parsedUrl) => {
  let firstQueryParamIndex =
    try(String.index(queryParams, '=')) {
    | Not_found => (-1)
    };
  if (firstQueryParamIndex == (-1)) {
    None;
  } else {
    let accessToken =
      String.split_on_char('=', queryParams)
      |> Array.of_list
      |> Array.get(_, 1)
      |> String.split_on_char('&')
      |> List.hd;
    let state =
      String.split_on_char('=', queryParams)
      |> Array.of_list
      |> Array.get(_, 4)
      |> String.split_on_char('&')
      |> List.hd;
    Some({accessToken, state});
  };
};

let getAccessToken = (url: string): option(string) => {
  let queryParamsStartIndex =
    try(String.index(url, '#')) {
    | Not_found => (-1)
    };
  if (queryParamsStartIndex == (-1)) {
    None;
  } else {
    switch (String.split_on_char('#', url)) {
    | [_baseUrl, queryParams] =>
      switch (parseQueryParams(queryParams)) {
      | Some({accessToken, state}) => Some(accessToken)
      | None => None
      }
    };
  };
};

let getState = (url: string): option(string) => {
  let queryParamsStartIndex =
    try(String.index(url, '#')) {
    | Not_found => (-1)
    };
  if (queryParamsStartIndex == (-1)) {
    None;
  } else {
    switch (String.split_on_char('#', url)) {
    | [_baseUrl, queryParams] =>
      switch (parseQueryParams(queryParams)) {
      | Some({accessToken, state}) => Some(state)
      | None => None
      }
    };
  };
};
