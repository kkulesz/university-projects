import React, { useEffect, useState } from 'react'

import { Link, useNavigate } from 'react-router-dom';

import { createActivity } from '../dataSource/activitiesApi';
import { fetchActiveProjects } from '../dataSource/projectsApi'
import { useGlobalState } from '../state'

const ChangeDateForm = () => {
    const navigate = useNavigate();

    const { chosenDay, setDay,
        chosenMonth, setMonth,
        chosenYear, setYear } = useGlobalState()
    return (
        <div>
            <form onSubmit={() => navigate("/activitiesDashboard")}>
                <label>
                    Year:
                    <input type="number" name="year" value={chosenYear} onChange={(e) => setYear(e.target.value)} />
                </label>
                <label>
                    Month:
                    <input type="number" name="month" value={chosenMonth} onChange={(e) => setMonth(e.target.value)} />
                </label>
                <label>
                    Day:
                    <input type="number" name="day" value={chosenDay} onChange={(e) => setDay(e.target.value)} />
                </label>
                <div>
                    <input type="submit" value="Change date" />
                </div>
            </form>
            <Link to="/activitiesDashboard">
                Back
            </Link>
        </div>
    )

}

export default ChangeDateForm;
