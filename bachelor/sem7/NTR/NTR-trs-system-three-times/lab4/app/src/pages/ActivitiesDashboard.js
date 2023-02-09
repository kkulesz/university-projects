import React, { useEffect, useState } from 'react'
import { Link } from 'react-router-dom';

import ActivitesList from '../components/ActivitiesList'
import { fetchActivitiesForDay } from '../dataSource/activitiesApi'
import { useGlobalState } from '../state'

const ActivitiesDashboard = () => {
  const { loggedUser, chosenDay, chosenMonth, chosenYear } = useGlobalState()

  const [activities, setActivities] = useState([])
  useEffect(() => {
    fetchActivitiesForDay(chosenYear, chosenMonth, chosenDay, loggedUser)
      .then((res) => { setActivities(res) })
  }, [])

  const summedBudget = activities.reduce(
    (acc, curr) => parseInt(acc) + parseInt(curr.budget), 0
  )
  return (
    <div>
      <div>
        {chosenYear}-{chosenMonth}-{chosenDay}
      </div>
      <Link to="/changeDate">
        change chosen date
      </Link>
      <div>
        <ActivitesList activities={activities} />
      </div>
      <div>
        Todal budget: {summedBudget}
      </div>

      <Link to="/createActivityForm">
        Create new activity
      </Link>
      <div></div>


    </div>
  )

}

export default ActivitiesDashboard;
