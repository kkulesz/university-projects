import React, { useEffect, useState } from 'react'

import { Link, useLocation } from 'react-router-dom';

const DisplayActivity = () => {
    const location = useLocation()
    const activity = location.state.activity

    return (
        <div>
            code={activity.code}, budget={activity.budget}, project={activity.project}
            <br />
            <Link to="/activitiesDashboard">
                Back
            </Link>
        </div>
    )
}

export default DisplayActivity;
