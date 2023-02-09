import './css/index.css';

import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';
import { AppState } from './state';

ReactDOM.render(
  <React.StrictMode>
    <AppState>
      <App />
    </AppState>
  </React.StrictMode>,
  document.getElementById('root')
);
