// Description: A pattern for the LED matrix

import {green, black} from './colors';

const backgroundColor = black;

export const frown = [
  // Line one
  [
    backgroundColor,
    backgroundColor,
    green,
    green,
    green,
    green,
    backgroundColor,
    backgroundColor,
  ],
  // Line two
  [
    backgroundColor,
    green,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    green,
    backgroundColor,
  ],
  // Line three
  [
    green,
    backgroundColor,
    green,
    backgroundColor,
    backgroundColor,
    green,
    backgroundColor,
    green,
  ],
  // Line four
  [
    green,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    green,
  ],
  // Line five
  [
    green,
    backgroundColor,
    backgroundColor,
    green,
    green,
    backgroundColor,
    backgroundColor,
    green,
  ],
  // Line six
  [
    green,
    backgroundColor,
    green,
    backgroundColor,
    backgroundColor,
    green,
    backgroundColor,
    green,
  ],
  // Line seven
  [
    backgroundColor,
    green,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    green,
    backgroundColor,
  ],
  // Line eight
  [
    backgroundColor,
    backgroundColor,
    green,
    green,
    green,
    green,
    backgroundColor,
    backgroundColor,
  ],
];
