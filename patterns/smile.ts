// Description: A smile pattern for the LED matrix

import {green, black} from './colors';

const backgroundColor = black;

export const smile = [
  // Line one
  [
    backgroundColor,
    backgroundColor,
    green,
    green,
    green,
    green,
    green,
    backgroundColor,
  ],
  // Line two
  [
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
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
    green,
    backgroundColor,
    backgroundColor,
    green,
    backgroundColor,
    green,
  ],
  // Line six
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
