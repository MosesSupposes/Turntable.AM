type parsedUrl = {
  accessToken: string,
  stateKey: string,
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
    let stateKey =
      String.split_on_char('=', queryParams)
      |> Array.of_list
      |> Array.get(_, 4)
      |> String.split_on_char('&')
      |> List.hd;
    Some({accessToken, stateKey});
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
      | Some({accessToken, stateKey}) => Some(accessToken)
      | None => None
      }
    };
  };
};

let getStateKey = (url: string): option(string) => {
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
      | Some({accessToken, stateKey}) => Some(stateKey)
      | None => None
      }
    };
  };
};
