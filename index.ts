import express, {Express, Request, Response} from 'express';
import dotenv from 'dotenv';
import winston, {transports, QueryOptions, format} from 'winston';
import { heart } from './patterns/heart';
import { blank } from './patterns/blank';
import { smile } from './patterns/smile';
import { kiss } from './patterns/kiss';
import { frown } from './patterns/frown';
import { flower } from './patterns/flower';

dotenv.config();

const app: Express = express();
const key = process.env.KEY || 'default';
const port = process.env.PORT || 3000;
const logLevel = process.env.LOG_LEVEL || 'info';
const logger = winston.createLogger({
  level: logLevel,
  transports: [
    new transports.Console({format: winston.format.simple()}),
    new transports.File({filename: 'log.log', level: 'info'}),
    new transports.File({filename: 'error.log', level: 'debug'}),
  ],
});

app.get('/:getId', (req: Request, res: Response) => {
  if (req?.query?.key !== key) {
    res.status(401).json('Invalid key');
    return;
  }
  let patternResponse: Array<any> = [];

  // const oneDay = 24 * 60 * 60 * 1000;
  const twoMinutes = 2 * 60 * 1000;
  const until = new Date();
  const from = new Date(until.valueOf() - twoMinutes);
  const options: QueryOptions = {
    from: from,
    until: until,
    limit: 10,
    start: 0,
    order: 'desc',
    fields: ['message', 'timestamp', 'level'],
  };
  logger.query(options, (err, results) => {
    if (err) {
      console.log(err);
      res.send(err);
    }
    const response = results?.file?.filter(
      (entry: any) => JSON.parse(entry?.message).toId === req.params.getId
    );
    let presses = "0";
    if (response?.length > 0) {
      presses = JSON.parse(response[0]?.message)?.presses;
    }
    if (presses === "1") {
      patternResponse = smile;
    } else if (presses === "2") {
      patternResponse = heart;
    } else if (presses === "3") {
      patternResponse = kiss;
    } else {
      patternResponse = flower;
    };
    res.status(200).json({ ledPattern: patternResponse });
  });
});

app.post('/:toId', (req: Request, res: Response) => {
  if (req?.query?.key !== key) {
    res.status(401).json('Invalid key');
    return;
  }
  const message = {
    toId: req?.params?.toId?.toString(),
    presses: req?.query?.presses?.toString(),
  };
  logger.log('info', JSON.stringify(message), {timestamp: new Date()});
  res.status(200).json(message);
});

app.listen(port, () => {
  console.log(`⚡️[server]: Server is running at http://localhost:${port}`);
});
