const nodemailer = require('nodemailer');
const transporter = nodemailer.createTransport({
  host: 'smtp.gmail.com',
  port: 465,
  auth: {
    user: 't110590450@ntut.org.tw',
    pass: 'mvioqzajaxgesfau',
  },
});

transporter.sendMail({
  from: 't110590450@ntut.org.tw',
  to: 't110590450@ntut.org.tw',
  subject: 'hihi',
  html: 'ncjwconeocnewoiwpji',
}).then(info => {
  console.log({ info });
}).catch(console.error);
