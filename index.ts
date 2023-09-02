import express, {Express, Request, Response} from 'express';
import dotenv from 'dotenv';
import winston, { transports, QueryOptions, format } from 'winston';

dotenv.config();

const app: Express = express();
const port = process.env.PORT || 3000;
const logLevel = process.env.LOG_LEVEL || 'info';
const logger = winston.createLogger({
  level: logLevel,
  transports: [
    new transports.Console({format: winston.format.simple()}),
    new transports.File({filename: 'log.log'}),
  ],
});

app.get('/:getId', (req: Request, res: Response) => {
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
    fields: ['message', 'timestamp', 'level']
  };
  logger.query(options, (err, results) => {
    if (err) {
      console.log(err);
      res.send(err);
    }
    const response = results?.file?.filter((entry: any) => JSON.parse(entry?.message).toId === req.params.getId);
    res.send(response[0].message || {'message': 'No messages found'});
  });
});

app.post('/:toId', (req: Request, res: Response) => {
  const message = {
    toId: req?.params?.toId?.toString(),
    message: req?.query?.message?.toString(),
    presses: req?.query?.presses?.toString(),
  };
  logger.log('info', JSON.stringify(message), { timestamp: new Date() });
  res.send(JSON.stringify(message));
});

app.listen(port, () => {
  console.log(`⚡️[server]: Server is running at http://localhost:${port}`);
});

