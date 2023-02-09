import React, { useEffect, useState } from 'react'
import CreateUserForm from '../components/CreateUserForm'
import UsersList from '../components/UsersList'

import { fetchUsers } from '../dataSource/usersApi'

const Start = () => {
  const [users, setUsers] = useState([])
  useEffect(() => {
    fetchUsers().then((res) => {
      setUsers(res)
    })
  }, [])

  return (
    <div>
      <UsersList users={users} />
      <CreateUserForm />
    </div>
  )

}

export default Start;
