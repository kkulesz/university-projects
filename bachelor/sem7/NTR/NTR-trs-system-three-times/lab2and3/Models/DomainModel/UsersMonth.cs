using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Collections.Generic;
using System;

namespace lab2and3.Models.DomainModel
{
    public record UsersMonth
    {
        public Guid UsersMonthId { get; init; }
        public int Year { get; init; }
        public int Month { get; init; }
        [MaxLength(50)]
        public string UserLogin { get; init; }
        public bool Frozen { get; init; }

        public DateTime CreatedAt { get; init; } = DateTime.Now;

        public DateTime NextMonth()
        {
            if (Month == 12)
                return new DateTime(Year + 1, 1, 1);
            return new DateTime(Year, Month + 1, 1);
        }

        public DateTime PreviousMonth()
        {
            if (Month == 1)
                return new DateTime(Year - 1, 12, 1);
            return new DateTime(Year, Month - 1, 1);
        }

        public DateTime ThisMonth()
        {
            return new DateTime(Year, Month, 1);
        }
    }
}