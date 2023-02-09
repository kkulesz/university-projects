import React from 'react';
import { Link } from 'react-router-dom';
import { useGlobalState } from '../state';


const NavigationBar = () => {
  const { loggedUser } = useGlobalState();


  return (
    <header>
      <h4>logged as: {loggedUser}</h4>
      <nav>
        <div>
          <Link to="/">
            Home
          </Link>

          <Link to="/activitiesDashboard">
            Activities
          </Link>

          <Link to="/projectsDashboard">
            Projects
          </Link>
        </div>
      </nav>
    </header>
  )

}

export default NavigationBar;
